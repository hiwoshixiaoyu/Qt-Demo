#include "LibAudio.h"
#include <QSound>


IMPLEMENT_SINGLETON(LibAudio)

LibAudio::LibAudio()
{
    //设置音量
     musicPlayer.setVolume(80);
}

LibAudio::~LibAudio()
{

}



void LibAudio::playSound(QString url)
{
    QSound::play(url);
    return;
}


QT_RESULT LibAudio::playMusic(QString url, bool isRepeat)
{
    if(isRepeat)
    {
        playlist.clear();
        playlist.addMedia(QUrl(url));
        playlist.setCurrentIndex(1);
        playlist.setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        musicPlayer.setPlaylist(&playlist);
        musicPlayer.play();
        return QT_SUCCESS;
    }

    musicPlayer.setMedia(QUrl::fromLocalFile(url));
    musicPlayer.play();
    return QT_SUCCESS;
}

QT_RESULT LibAudio::pauseMusic()
{
    musicPlayer.pause();
    return QT_SUCCESS;
}

QT_RESULT LibAudio::continueMusic()
{
    musicPlayer.play();
    return QT_SUCCESS;
}

QT_RESULT LibAudio::stopMusic()
{
    musicPlayer.stop();
    return QT_SUCCESS;
}
