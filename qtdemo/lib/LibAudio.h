#ifndef LIBAUDIO_H
#define LIBAUDIO_H

#include "common.h"


#include <QMediaPlayer>
#include <QMediaPlaylist>
class LibAudio
{

   DECLARE_SINGLETON(LibAudio)

public:
    LibAudio();
     virtual ~LibAudio();
    //播放简短音乐 wav格式
    void playSound(QString url);

    //播放其它格式音乐
    QT_RESULT playMusic(QString url,bool isRepeat=false);
    QT_RESULT pauseMusic();
    QT_RESULT continueMusic();
    QT_RESULT stopMusic();

private:
    QMediaPlayer musicPlayer;
    QMediaPlaylist  playlist;
};

#endif // LIBAUDIO_H
