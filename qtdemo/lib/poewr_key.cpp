#include "poewr_key.h"

#include <QDebug>
#include <QProcess>
#include <QNetworkInterface>
#include <windows.h>
#include <QTime>

Poewr_Key::Poewr_Key()
{

}

Poewr_Key::~Poewr_Key()
{

}

const QString Poewr_Key::getPCCode()
{
    QString strCpuId = getCpuId().mid(0,3);
    QString strMacAdress = getMacAddress().mid(0,3);
    QString strDiskNum = getDiskNumber().mid(0,3);
    QString strMacAdress2 = getMacAddress().mid(4,3);
    QString code ="C"+strCpuId+"-M"+strMacAdress+"-D"+strDiskNum+"-A"+strMacAdress2;

    qDebug()<<code<<endl;
     //反转
    CharAtreverse(code);
    return code;
}

//3位校验码+年--cmdm组合-cmdm组合-cmdm组合-月cmd
const QString Poewr_Key::generateKey(QString str)
{
    CharAtreverse(str);
    QString a;


    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i=0; i<10; i++)
    {
        int test =qrand()%10;
        QChar num = 'A'+qrand()%24;
        qDebug()<<test<<endl;
        qDebug()<<num<<endl;
    }


    return a;
}

//3位校验码+年--cmdm组合--cmdm组合--cmdm组合--月+cmd
bool Poewr_Key::checkCode(const QString &str)
{
    //反转解密
    //验证随机数1~5 A~Z 4位
    //验证cpuid
    //验证disk
    //验证mac
    return false;
}

QString Poewr_Key::toXOREncryptUncrypt(QString src, const QChar key)
{
    for(int i = 0; i < src.count(); i++) {
        src[i] = src.at(i).toLatin1() ^ key.toLatin1();
    }
    return src;
}

void Poewr_Key::CharAtreverse(QString &word)
{
    QChar temp;
    size_t i, j;
    for (j = 0, i = word.size() - 1; j < i; --i, ++j) {
        temp = word[i];
        word[i] = word[j];
        word[j] = temp;
    }
}


/*
 * MD5加密
 */
const QString Poewr_Key::hash_Encryption(const QString temp)
{
    QByteArray byte_array;
    byte_array.append(temp);
    QByteArray hash_byte_array = QCryptographicHash::hash(byte_array,QCryptographicHash::Md5);
    return hash_byte_array.toHex().toUpper();
}
/*
 * 格式化生成序列号
 */
const QString Poewr_Key::format_HASHString(const QString hashtemp)
{
    QString retemp = "";
    for(int i = 0; i < 7; i++)
    {
        retemp += hashtemp.mid(4*i,4) + "-";
    }
    retemp += hashtemp.mid(28,4);
    return retemp;
}
/*
 * 去除格式，还原MD5序列
 */
const QString Poewr_Key::remove_Format(const QString formathash)
{
    QString temp = "";
    for(int i = 0; i < 8; i++)
    {
        temp += formathash.mid(5*i,4);
    }
    return temp;
}



const QString Poewr_Key::getDiskNumber()
{

    QString lpRootPathName = "C:\\";
    LPTSTR lpVolumeNameBuffer=new TCHAR[12];//磁盘卷标
    DWORD nVolumeNameSize=12;// 卷标的字符串长度
    DWORD VolumeSerialNumber;//硬盘序列号
    DWORD MaximumComponentLength;// 最大的文件长度
    LPTSTR lpFileSystemNameBuffer=new TCHAR[10];// 存储所在盘符的分区类型的长指针变量
    DWORD nFileSystemNameSize=10;// 分区类型的长指针变量所指向的字符串长度
    DWORD FileSystemFlags;// 文件系统的一此标志

    GetVolumeInformation((LPTSTR)lpRootPathName.utf16(),
                         lpVolumeNameBuffer, nVolumeNameSize,
                         &VolumeSerialNumber, &MaximumComponentLength,
                         &FileSystemFlags,
                         lpFileSystemNameBuffer, nFileSystemNameSize);

    return QString::number(VolumeSerialNumber,10);
}

const QString Poewr_Key::getCpuId()
{
    QString cpuId = "";
    QProcess p(0);
    p.start("wmic CPU get ProcessorID");
    p.waitForStarted();
    p.waitForFinished();
    cpuId = QString::fromLocal8Bit(p.readAllStandardOutput());
    cpuId = cpuId.remove("ProcessorId").trimmed();
    return cpuId;
}

const QString Poewr_Key::getMacAddress()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
    int nCnt = nets.count();
    QString strMacAddr = "";
    for (int i = 0; i < nCnt; i++)
    {
        strMacAddr = nets[i].hardwareAddress();
        if (strMacAddr.isEmpty())
        {
            continue;
        }
        break;
    }
    strMacAddr.replace(":", "");
    return strMacAddr.toLocal8Bit();
}


void Poewr_Key::base64Code(QString &str)
{
   str =  str.toLocal8Bit().toBase64();
    qDebug()<<str<<endl;
}

void Poewr_Key::decodeBase64(QString &str)
{
    QByteArray text = str.toLocal8Bit();
    QByteArray by = text.fromBase64(text);
    str = QString::fromLocal8Bit(by);
}
