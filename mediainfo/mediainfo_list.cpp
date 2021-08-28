//--------------------------------------------------------------------
//
// Source File created by Python3.9.6 2021-08-28T05:47:20
// For MediaInfo v18.08 or greater version.
// The macro definition is derived from the CSV files in Developers/List_Of_Parameters.
// More: https://github.com/MediaArea/MediaInfoLib/blob/master/Source/MediaInfo/File__Analyse_Automatic.h
//
//--------------------------------------------------------------------

#include "mediainfo_list.h"

///@brief Kinds of Stream: general
///extern QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_general;
///
QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_general = {
};

///@brief Kinds of Stream: video
///extern QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_video;
///
QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_video = {
};

///@brief Kinds of Stream: audio
///extern QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_audio;
///
QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_audio = {
};

///@brief Kinds of Stream: text
///extern QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_text;
///
QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_text = {
};

///@brief Kinds of Stream: other
///extern QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_other;
///
QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_other = {
};

///@brief Kinds of Stream: image
///extern QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_image;
///
QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_image = {
};

///@brief Kinds of Stream: menu
///extern QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_menu;
///
QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>> g_mediainfo_list_menu = {
};

QList<QPair<QString, QList<QPair<MediaInfoDLL::String, QPair<QString, bool>>>>> g_mediainfo_lists = {
	{ "General", g_mediainfo_list_general },  // Stream_General
	{ "Video",   g_mediainfo_list_video   },  // Stream_Video
	{ "Audio",   g_mediainfo_list_audio   },  // Stream_Audio
	{ "Text",    g_mediainfo_list_text    },  // Stream_Text
	{ "Other",   g_mediainfo_list_other   },  // Stream_Other
	{ "Image",   g_mediainfo_list_image   },  // Stream_Image
	{ "Menu",    g_mediainfo_list_menu    },  // Stream_Menu
};
