#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QPaintEvent>
#include <QPixmap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPainter>
#include <QDir>
#include <QFile>
#include <QtDebug>
/**
 *  开发者：い 狂奔的蜗牛
 *  描述：支持本地图片加载和网络图片加载的ImageView，并支持缓存。
 *  由于第一版并未实际用于项目，可能存在部分问题，可自行修改扩展
 */
class ImageView : public QWidget
{
    Q_OBJECT
public:
    ImageView(QWidget *parent = 0);
    enum STATE {
        loading,//标示加载中
        succeed,//标示加载成功
        failed//标示加载失败
    };
    enum STYLE {
        cover,//以长度小的一边为基准 显示中间位置
        contain,//完整显示图片 两边留空白
        percentage//以控件大小为基准，会失真
    };
public slots:
    void slotReplyPixmapLoad(QNetworkReply *);
protected:
    void paintEvent(QPaintEvent *);//重写绘制方法
private:
    //属性
    QPixmap loadingPixmap;//加载中
    QPixmap succeedPixmap;//加载成功
    QPixmap failedPixmap;//加载失败
    int mState;//标示状态  加载中 加载成功 加载事变
    int mStyle;//标示显示样式
    QString mUrl;//路径
    QString cacheDir;//缓存目录
    QNetworkAccessManager *mManager;
    void setSucceedPixmap(QPixmap );//设置加载成功的图片
public:
    //方法
    void setLoadingPixmap(QPixmap );//设置加载中图片
    void setFailedPixmap(QPixmap );//设置加载失败图片
    void setDisplayStyle(STYLE);//设置图片显示样式
    void setUrl(QString);//图片路径
    QPixmap getSucceedPixmap();//获取加载成功后的图片
};

#endif // IMAGEVIEW_H
