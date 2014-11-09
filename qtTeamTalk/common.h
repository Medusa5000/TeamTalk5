/*
 * Copyright (c) 2005-2014, BearWare.dk
 * 
 * Contact Information:
 *
 * Bjoern D. Rasmussen
 * Skanderborgvej 40 4-2
 * DK-8000 Aarhus C
 * Denmark
 * Email: contact@bearware.dk
 * Phone: +45 20 20 54 59
 * Web: http://www.bearware.dk
 *
 * This source code is part of the TeamTalk 5 SDK owned by
 * BearWare.dk. All copyright statements may not be removed 
 * or altered from any source distribution. If you use this
 * software in a product, an acknowledgment in the product 
 * documentation is required.
 *
 */

#ifndef COMMON_H
#define COMMON_H

#include <QDebug>
#include <QSettings>
#include <QList>
#include <QDomDocument>
#include <QPainter>
#include <QLayout>
#include <QComboBox>
#include <QFile>

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#pragma warning(disable:4800)
#endif

#ifdef Q_OS_WIN32
#define NOMINMAX //prevent std::...::min() collision
#include <windows.h>
#endif

#include <TeamTalk.h>

#if defined(Q_OS_DARWIN) //For hotkeys on Mac
#include <Carbon/Carbon.h>
#endif

#if defined(Q_OS_WINCE)
#define _W(qstr) qstr.utf16()
#define _Q(wstr) QString::fromWCharArray(wstr)
#define COPY_TTSTR(wstr, qstr)                                      \
    do {                                                            \
        wcsncpy(wstr, _W(qstr), TT_STRLEN);                         \
        if(qstr.size() >= TT_STRLEN)                                \
            wstr[TT_STRLEN-1] = '\0';                               \
    } while(0)

#elif defined(Q_OS_WIN32)
//Conversion from/to TTCHAR
#define _W(qstr) qstr.toStdWString().c_str()
#define _Q(wstr) QString::fromWCharArray(wstr)
#define COPY_TTSTR(wstr, qstr)                                      \
    do {                                                            \
        wcsncpy(wstr, _W(qstr), TT_STRLEN);                         \
        if(qstr.size() >= TT_STRLEN)                                \
            wstr[TT_STRLEN-1] = '\0';                               \
    } while(0)

#else
#define _W(qstr) qstr.toUtf8().constData()
#define _Q(wstr) QString::fromUtf8(wstr)
#define COPY_TTSTR(wstr, qstr)                                      \
    do {                                                            \
        strncpy(wstr, _W(qstr), TT_STRLEN);                         \
        if(qstr.size() >= TT_STRLEN)                                \
            wstr[TT_STRLEN-1] = '\0';                               \
    } while(0)
#endif

#define ZERO_STRUCT(a) memset(&a, 0, sizeof(a))

#ifdef ENABLE_ENCRYPTION

#define DEFAULT_TCPPORT 10443
#define DEFAULT_UDPPORT 10443

#else

#define DEFAULT_TCPPORT 10333
#define DEFAULT_UDPPORT 10333

#endif

//Client specific SOUND_VOLUME_MAX (volume slider)
#define DEFAULT_SOUND_VOLUME_MAX        12000
#define VOLUME_SINGLE_STEP              25
#define VOLUME_PAGE_STEP                200

//Client specific gain SOUND_GAIN_MAX (mic slider)
#define DEFAULT_GAIN_MAX                6000
//Client spefic VU max SOUND_VU_MAX (voice act slider)
#define DEFAULT_SOUND_VU_MAX            20

#define DEFAULT_AGC_ENABLE              TRUE
#define DEFAULT_AGC_GAINLEVEL           8000
#define DEFAULT_AGC_INC_MAXDB           12
#define DEFAULT_AGC_DEC_MAXDB           -40
#define DEFAULT_AGC_GAINMAXDB           30
#define DEFAULT_DENOISE_ENABLE          TRUE
#define DEFAULT_DENOISE_SUPPRESS        -30
#define DEFAULT_ECHO_SUPPRESS           -40
#define DEFAULT_ECHO_SUPPRESSACTIVE     -15

//Default audio config settings
#if defined(Q_OS_LINUX) || defined(Q_OS_DARWIN)
#define DEFAULT_SOUND_DUPLEXMODE        TRUE
#define DEFAULT_ECHO_ENABLE             TRUE
#else
//Windows performs poorly with echo cancel so disable it
#define DEFAULT_SOUND_DUPLEXMODE        FALSE
#define DEFAULT_ECHO_ENABLE             FALSE
#endif


#define DEFAULT_MSEC_PER_PACKET         40

#define DEFAULT_AUDIOCODEC              OPUS_CODEC

//Default Speex codec settings
#define DEFAULT_SPEEX_BANDMODE          1
#define DEFAULT_SPEEX_QUALITY           4
#define DEFAULT_SPEEX_DELAY             DEFAULT_MSEC_PER_PACKET
#define DEFAULT_SPEEX_SIMSTEREO         FALSE

//Default Speex VBR codec settings
#define DEFAULT_SPEEX_VBR_BANDMODE      1
#define DEFAULT_SPEEX_VBR_QUALITY       4
#define DEFAULT_SPEEX_VBR_BITRATE       0
#define DEFAULT_SPEEX_VBR_MAXBITRATE    0
#define DEFAULT_SPEEX_VBR_DTX           TRUE
#define DEFAULT_SPEEX_VBR_DELAY         DEFAULT_MSEC_PER_PACKET
#define DEFAULT_SPEEX_VBR_SIMSTEREO     FALSE

//Default OPUS codec settings
#define DEFAULT_OPUS_SAMPLERATE     48000
#define DEFAULT_OPUS_CHANNELS       1
#define DEFAULT_OPUS_APPLICATION    OPUS_APPLICATION_VOIP
#define DEFAULT_OPUS_COMPLEXITY     10
#define DEFAULT_OPUS_FEC            TRUE
#define DEFAULT_OPUS_DTX            FALSE
#define DEFAULT_OPUS_VBR            TRUE
#define DEFAULT_OPUS_VBRCONSTRAINT  FALSE
#define DEFAULT_OPUS_BITRATE        32000
#define DEFAULT_OPUS_DELAY          DEFAULT_MSEC_PER_PACKET

//Default video capture settings
#define DEFAULT_VIDEO_WIDTH     320
#define DEFAULT_VIDEO_HEIGHT    240
#define DEFAULT_VIDEO_FPS       10
#define DEFAULT_VIDEO_FOURCC    FOURCC_RGB32

//Default video codec settings
#define DEFAULT_VIDEO_CODEC     WEBM_VP8_CODEC
#define DEFAULT_WEBMVP8_BITRATE 256

//Default user right for default user-type
#define USERRIGHT_DEFAULT   (USERRIGHT_MULTI_LOGIN |                \
                             USERRIGHT_VIEW_ALL_USERS |             \
                             USERRIGHT_CREATE_TEMPORARY_CHANNEL |   \
                             USERRIGHT_UPLOAD_FILES |               \
                             USERRIGHT_DOWNLOAD_FILES |             \
                             USERRIGHT_TRANSMIT_VOICE |             \
                             USERRIGHT_TRANSMIT_VIDEOCAPTURE |      \
                             USERRIGHT_TRANSMIT_DESKTOP |           \
                             USERRIGHT_TRANSMIT_DESKTOPINPUT |      \
                             USERRIGHT_TRANSMIT_MEDIAFILE_AUDIO |   \
                             USERRIGHT_TRANSMIT_MEDIAFILE_VIDEO)

//whether to enable key-translation
#define ENABLE_KEY_TRANSLATION 1

#ifdef Q_OS_WIN32
#define WM_TEAMALK_CLIENTEVENT     (WM_APP + 1)
#define WM_TEAMTALK_HOTKEYEVENT     (WM_APP + 2)
#endif

//For TT_DoChangeStatus
enum StatusMode
{
    STATUSMODE_AVAILABLE        = 0x00000000,
    STATUSMODE_AWAY             = 0x00000001, 
    STATUSMODE_QUESTION         = 0x00000002,
    STATUSMODE_MODE             = 0x000000FF,

    STATUSMODE_FLAGS            = 0xFFFFFF00,
    STATUSMODE_FEMALE           = 0x00000100,
    STATUSMODE_VIDEOTX          = 0x00000200,
    STATUSMODE_DESKTOP          = 0x00000400,
    STATUSMODE_STREAM_MEDIAFILE = 0x00000800
};

enum Gender
{
    GENDER_NONE             = 0,
    GENDER_MALE             = 1,
    GENDER_FEMALE           = 2
};

enum SoundEvent
{
    SOUNDEVENT_NEWUSER,
    SOUNDEVENT_REMOVEUSER,
    SOUNDEVENT_SERVERLOST,
    SOUNDEVENT_USERMSG,
    SOUNDEVENT_CHANNELMSG,
    SOUNDEVENT_HOTKEY,
    SOUNDEVENT_SILENCE,   
    SOUNDEVENT_NEWVIDEO,   
    SOUNDEVENT_NEWDESKTOP,   
    SOUNDEVENT_FILESUPD,  
    SOUNDEVENT_FILETXDONE,
    SOUNDEVENT_QUESTIONMODE,
    SOUNDEVENT_DESKTOPACCESS,
};

enum HotKeyID
{
    HOTKEY_PUSHTOTALK,
    HOTKEY_VOICEACTIVATION,
    HOTKEY_INCVOLUME,
    HOTKEY_DECVOLUME,
    HOTKEY_MUTEALL,
    HOTKEY_MICROPHONEGAIN_INC,
    HOTKEY_MICROPHONEGAIN_DEC,
    HOTKEY_VIDEOTX
};

typedef QList<INT32> hotkey_t;

#if defined(Q_OS_DARWIN)
#define MAC_HOTKEY_SIZE 2
#define MAC_NO_KEY 0xFFFFFFFF
#endif

enum AudioStorageMode
{
    AUDIOSTORAGE_NONE               = 0x0,
    AUDIOSTORAGE_SINGLEFILE         = 0x1,
    AUDIOSTORAGE_SEPARATEFILES      = 0x2
};

enum DesktopShareMode
{
    DESKTOPSHARE_NONE,
    DESKTOPSHARE_DESKTOP,
    DESKTOPSHARE_ACTIVE_WINDOW,
    DESKTOPSHARE_SPECIFIC_WINDOW,
};

enum VideoText
{
    VIDEOTEXT_NONE                   = 0x0000,
    VIDTEXT_POSITION_MASK            = 0x000F,
    VIDTEXT_POSITION_TOPLEFT         = 0x0001,
    VIDTEXT_POSITION_TOPRIGHT        = 0x0002,
    VIDTEXT_POSITION_BOTTOMLEFT      = 0x0003,
    VIDTEXT_POSITION_BOTTOMRIGHT     = 0x0004,

    VIDTEXT_SHOW_MASK                = 0x00F0,
    VIDTEXT_SHOW_NICKNAME            = 0x0010,
    VIDTEXT_SHOW_USERNAME            = 0x0020,
    VIDTEXT_SHOW_STATUSTEXT          = 0x0040,
};

struct HostEntry
{
    QString name;
    QString ipaddr;
    int tcpport;
    int udpport;
    bool encrypted;
    QString username;
    QString password;
    QString channel;
    QString chanpasswd;
    //tt-file specific
    QString nickname;
    Gender gender;
    hotkey_t hotkey;
    int voiceact;
    VideoFormat capformat;
    VideoCodec vidcodec;

    HostEntry()
    : tcpport(0), udpport(0), encrypted(false), gender(GENDER_NONE)
    , voiceact(-1), capformat(), vidcodec() {}
};

struct DesktopAccessEntry
{
    QString ipaddr;
    int tcpport;
    QStringList channels;
    QStringList usernames;
    DesktopAccessEntry()
    : tcpport(0) { }
};

//internal TeamTalk 5 commands. Use with TT_DoTextMessage() and 
//message type MSGTYPE_CUSTOM
#define TT_INTCMD_TYPING_TEXT         "typing"
#define TT_INTCMD_DESKTOP_ACCESS      "desktopaccess"

typedef QList<TextMessage> textmessages_t;

QString makeCustomCommand(const QString& cmd, const QString& value);
QStringList getCustomCommand(const TextMessage& msg);

void initDefaultAudioCodec(AudioCodec& codec);
bool getVideoCaptureCodec(VideoCodec& vidcodec);

bool initVideoCaptureFromSettings();
bool initVideoCapture(const QString& devid, const VideoFormat& fmt);
bool isValid(const VideoFormat& fmt);


bool getSoundDevice(int deviceid, const QVector<SoundDevice>& devs, SoundDevice& dev);
bool getSoundDevice(const QString& devid, const QVector<SoundDevice>& devs, SoundDevice& dev);

int getDefaultSndInputDevice();
int getDefaultSndOutputDevice();

int getSoundInputFromUID(int inputid, const QString& uid);
int getSoundOutputFromUID(int outputid, const QString& uid);

int getSelectedSndInputDevice();
int getSelectedSndOutputDevice();

QString getHotKeyText(const hotkey_t& hotkey);

bool isComputerIdle(int idle_secs);

void saveHotKeySettings(HotKeyID hotkeyid, const hotkey_t& hotkey);

bool loadHotKeySettings(HotKeyID hotkeyid, hotkey_t& hotkey);

void deleteHotKeySettings(HotKeyID hotkeyid);

void playSoundEvent(SoundEvent event);

void addLatestHost(const HostEntry& host);
bool getLatestHost(int index, HostEntry& host);

//server entries in settings file
void addServerEntry(const HostEntry& host);
void setServerEntry(int index, const HostEntry& host);
bool getServerEntry(int index, HostEntry& host);
void deleteServerEntry(const QString& name);

//server entry from XML
bool getServerEntry(const QDomElement& hostElement, HostEntry& entry);
#define CLIENTSETUP_TAG "clientsetup"

//get desktop access list
void addDesktopAccessEntry(const DesktopAccessEntry& entry);
void getDesktopAccessList(QVector<DesktopAccessEntry>& entries);
void getDesktopAccessList(QVector<DesktopAccessEntry>& entries,
                          const QString& ipaddr, int tcpport);
bool hasDesktopAccess(const QVector<DesktopAccessEntry>& entries,
                      const User& user);
void deleteDesktopAccessEntries();

QString newVersionAvailable(const QDomDocument& updateDoc);

QByteArray generateTTFile(const HostEntry& entry);

void incVolume(int userid, StreamType stream_type);
void decVolume(int userid, StreamType stream_type);

bool versionSameOrLater(const QString& check, const QString& against);
QString getVersion(const User& user);
QString limitText(const QString& text);

QString getDateTimeStamp();
QString generateAudioStorageFilename(AudioFileFormat aff);

QString generateLogFileName(const QString& name);
bool openLogFile(QFile& file, const QString& folder, const QString& name);
bool writeLogEntry(QFile& file, const QString& line);

void setVideoTextBox(const QRect& rect, const QColor& bgcolor,
                     const QColor& fgcolor, const QString& text,
                     quint32 text_pos, int w_percent, int h_percent,
                     QPainter& painter);

void setTransmitUsers(const QSet<int>& users, INT32* dest_array, INT32 max_elements);
#if defined(Q_OS_DARWIN)
void setMacResizeMargins(QDialog* dlg, QLayout* layout);
#endif /* Q_OS_DARWIN */

void setCurrentItemData(QComboBox* cbox, const QVariant& itemdata);
QVariant getCurrentItemData(QComboBox* cbox, const QVariant& not_found = QVariant());
#endif
