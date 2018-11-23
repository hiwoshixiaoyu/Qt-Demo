#ifndef POEWR_KEY_H
#define POEWR_KEY_H

#include <Windows.h>
#include <QString>
#include <QCryptographicHash>



class Poewr_Key
{

public:
    explicit Poewr_Key();
    ~Poewr_Key();

    //生成序列号
    const QString getPCCode();

    //生成密钥
    const QString generateKey(QString str);
    //检查序列号
    bool checkCode(const QString &str);


    //异或
    QString toXOREncryptUncrypt(QString src, const QChar key);
    //字符串取反
    void  CharAtreverse(QString &word);

    //64位加密
    void base64Code(QString &str);
    void decodeBase64(QString &str);

private:
    const QString hash_Encryption(const QString temp);
    const QString format_HASHString(const QString hashtemp);
    const QString remove_Format(const QString formathash);

    //MAC地址
    const QString getMacAddress();
    //CPU id
    const QString getCpuId();
    //硬盘序列号
    const QString getDiskNumber();

};

#endif // POEWR_KEY_H
