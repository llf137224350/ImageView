#include "imageview.h"

ImageView::ImageView(QWidget *parent)
    :QWidget(parent)
{

    this->mState = STATE::loading;
    this->mStyle = STYLE::percentage;
    //默认当前路径下的cache目录
    this->cacheDir = QDir::currentPath()+QDir::separator()+"cache";
    QDir dir(this->cacheDir);//判断缓存路径是否存在
    if(!dir.exists()){
        dir.mkdir(this->cacheDir);
    }
    this->mManager = new QNetworkAccessManager(this);
    connect(this->mManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotReplyPixmapLoad(QNetworkReply*)));

}
void ImageView::slotReplyPixmapLoad(QNetworkReply* reply)
{
    if(reply->error() == QNetworkReply::NoError)
    {
        //获取图片数据
        QByteArray bytes =  reply->readAll();
        QPixmap pixmap;
        pixmap.loadFromData(bytes);
        this->setSucceedPixmap(pixmap);
        //使用路径生成md5
        QString md5;
        QByteArray bb = QCryptographicHash::hash ( this->mUrl.toUtf8(), QCryptographicHash::Md5 );
        md5.append(bb.toHex());
        //写入缓存
        QFile file(this->cacheDir+QDir::separator() + md5);
        if(!file.exists()){
            file.open(QIODevice::WriteOnly);
            file.close();
        }
        if (file.open(QIODevice::Append)){
            file.write(bytes);
        }
        file.close();
    }else{
        this->mState = STATE::failed;
        repaint();
    }
    this->mManager->deleteLater();

}
void ImageView::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);

    if(this->mState == STATE::succeed){//加载成功
        if(mStyle == STYLE::cover){
            //动态计算长的一边 以短的为基准
            if( this->succeedPixmap.width() > this->succeedPixmap.height() ){// w / h =mw /  h
                float w =    this->width() * this->succeedPixmap.height() / this->height();
                //得道宽度
                p.drawPixmap(QRect(0,0,this->width(),this->height()),this->succeedPixmap,QRect((this->succeedPixmap.width() - w ) / 2,0,w,this->succeedPixmap.height()));
            }else{
                float h =    this->height() * this->succeedPixmap.width() / this->width();
                //得道宽度
                p.drawPixmap(QRect(0,0,this->width(),this->height()),this->succeedPixmap,QRect(0,(this->succeedPixmap.height() - h ) / 2,this->succeedPixmap.width(),h));
            }

        }else  if(mStyle == STYLE::percentage){//已控件自身为基准
            p.drawPixmap(QRect(0,0,this->width(),this->height()),this->succeedPixmap);
        }else  if(mStyle == STYLE::contain){//以长的为基准
            //计算宽高比
            if(this->succeedPixmap.width() > this->succeedPixmap.height()){
                //计算对应的高度
                QPixmap pixmap(this->succeedPixmap.width(), this->height() * this->succeedPixmap.width() / this->width());
                pixmap.fill(Qt::white);//用透明色填充
                QPainter paint(&pixmap);
                paint.drawPixmap(0,(pixmap.height() - this->succeedPixmap.height()) / 2,this->succeedPixmap.width(),this->succeedPixmap.height(),this->succeedPixmap);
                p.drawPixmap(QRect(0,0 ,this->width(),this->height()),pixmap);
            }else{
                QPixmap pixmap(this->width() * this->succeedPixmap.height() / this->height(),this->succeedPixmap.height());
                pixmap.fill(Qt::white);//用透明色填充
                QPainter paint(&pixmap);
                paint.drawPixmap((pixmap.width() - this->succeedPixmap.width()) / 2,0,this->succeedPixmap.width(),this->succeedPixmap.height(),this->succeedPixmap);
                p.drawPixmap(QRect(0,0 ,this->width(),this->height()),pixmap);
            }
        }
    }else if(this->mState == STATE::failed){//加载失败
        if(mStyle == STYLE::cover){
            //动态计算长的一边
            if( this->failedPixmap.width() > this->failedPixmap.height() ){// w / h =mw /  h
                float w =    this->width() * this->failedPixmap.height() / this->height();
                //得道宽度
                p.drawPixmap(QRect(0,0,this->width(),this->height()),this->failedPixmap,QRect((this->failedPixmap.width() - w ) / 2,0,w,this->failedPixmap.height()));
            }else{
                float h =    this->height() * this->failedPixmap.width() / this->width();
                //得道宽度
                p.drawPixmap(QRect(0,0,this->width(),this->height()),this->failedPixmap,QRect(0,(this->failedPixmap.height() - h ) / 2,this->failedPixmap.width(),h));
            }

        }else if( mStyle == STYLE::percentage){
            p.drawPixmap(QRect(0,0,this->width(),this->height()),this->failedPixmap);
        }else  if(mStyle == STYLE::contain){//以长的为基准
            //计算宽高比
            if(this->failedPixmap.width() > this->failedPixmap.height()){
                //计算对应的高度
                QPixmap pixmap(this->failedPixmap.width(), this->height() * this->failedPixmap.width() / this->width());
                pixmap.fill(Qt::white);//用透明色填充
                QPainter paint(&pixmap);
                paint.drawPixmap(0,(pixmap.height() - this->failedPixmap.height()) / 2,this->failedPixmap.width(),this->failedPixmap.height(),this->failedPixmap);
                p.drawPixmap(QRect(0,0 ,this->width(),this->height()),pixmap);
            }else{
                QPixmap pixmap(this->width() * this->failedPixmap.height() / this->height(),this->failedPixmap.height());
                pixmap.fill(Qt::white);//用透明色填充
                QPainter paint(&pixmap);
                paint.drawPixmap((pixmap.width() - this->failedPixmap.width()) / 2,0,this->failedPixmap.width(),this->failedPixmap.height(),this->failedPixmap);
                p.drawPixmap(QRect(0,0 ,this->width(),this->height()),pixmap);
            }
        }

    }else {//加载中
        if(mStyle == STYLE::cover){
            //动态计算长的一边
            if( this->loadingPixmap.width() > this->loadingPixmap.height() ){// w / h =mw /  h
                float w =    this->width() * this->loadingPixmap.height() / this->height();
                //得道宽度
                p.drawPixmap(QRect(0,0,this->width(),this->height()),this->loadingPixmap,QRect((this->loadingPixmap.width() - w ) / 2,0,w,this->loadingPixmap.height()));
            }else{
                float h =    this->height() * this->succeedPixmap.width() / this->width();
                //得道宽度
                p.drawPixmap(QRect(0,0,this->width(),this->height()),this->loadingPixmap,QRect(0,(this->loadingPixmap.height() - h ) / 2,this->loadingPixmap.width(),h));
            }

        }else if(mStyle == STYLE::percentage){//已控件自身为基准
            p.drawPixmap(QRect(0,0,this->width(),this->height()),this->loadingPixmap);
        }
        else  if(mStyle == STYLE::contain){//以长的为基准
            //计算宽高比
            if(this->loadingPixmap.width() > this->loadingPixmap.height()){
                //计算对应的高度
                QPixmap pixmap(this->loadingPixmap.width(), this->height() * this->loadingPixmap.width() / this->width());
                pixmap.fill(Qt::white);//用透明色填充
                QPainter paint(&pixmap);
                paint.drawPixmap(0,(pixmap.height() - this->loadingPixmap.height()) / 2,this->loadingPixmap.width(),this->loadingPixmap.height(),this->loadingPixmap);
                p.drawPixmap(QRect(0,0 ,this->width(),this->height()),pixmap);
            }else{
                QPixmap pixmap(this->width() * this->loadingPixmap.height() / this->height(),this->loadingPixmap.height());
                pixmap.fill(Qt::white);//用透明色填充
                QPainter paint(&pixmap);
                paint.drawPixmap((pixmap.width() - this->loadingPixmap.width()) / 2,0,this->loadingPixmap.width(),this->loadingPixmap.height(),this->loadingPixmap);
                p.drawPixmap(QRect(0,0 ,this->width(),this->height()),pixmap);
            }
        }
    }

}
//设置获取成功之后的图片
void ImageView::setSucceedPixmap(QPixmap p)
{
    this->succeedPixmap = p;
    this->mState = STATE::succeed;
    this->repaint();
}
//设置加载中的图片
void ImageView::setLoadingPixmap(QPixmap p)
{
    this->loadingPixmap = p;
}
//设置加载失败 显示的图片
void ImageView::setFailedPixmap(QPixmap p)
{
    this->failedPixmap = p;

}
//设置显示样式
void ImageView::setDisplayStyle(ImageView::STYLE style)
{
    this->mStyle = style;
}
//设置路径
void ImageView::setUrl(QString url)
{
    this->mUrl = url;
    //判断是否为网络路径
    if(this->mUrl.contains("http://") || this->mUrl.contains("https://") ){//网络图片
        //判断有没有缓存
        QString md5;
        QByteArray bb = QCryptographicHash::hash ( this->mUrl.toUtf8(), QCryptographicHash::Md5 );
        md5.append(bb.toHex());
        QFile file(this->cacheDir+QDir::separator() + md5);
        if(!file.exists()){//不存在 走网络
            qDebug()<<"网络加载";
            this->mState = STATE::loading;
            this->repaint();
            this->mManager->get(QNetworkRequest(url));
        }else{//存在 走本地
            if( file.open(QIODevice::ReadOnly)){
                QByteArray bytes =  file.readAll();
                QPixmap pixmap;
                pixmap.loadFromData(bytes);
                this->setSucceedPixmap(pixmap);
                qDebug()<<"本地加载";
            }else {
                this->mState = STATE::failed;
                repaint();
            }
        }
        file.close();
    }else{//本地图片
        this->setSucceedPixmap(QPixmap(url));
    }
}

//获取加载成功后的图片
QPixmap ImageView::getSucceedPixmap()
{
    return this->succeedPixmap;
}
