#ifndef _NGX_RTMP_DASH_TEMPLATES
#define _NGX_RTMP_DASH_TEMPLATES


#define NGX_RTMP_DASH_MANIFEST_HEADER                                          \
    "<?xml version=\"1.0\"?><MPD type=\"dynamic\" xmlns=\"urn:mpeg:dash:schema:mpd:2011\" xmlns:cenc=\"urn:mpeg:cenc:2013\" xmlns:mspr=\"urn:microsoft:playready\" availabilityStartTime=\"%s\" publishTime=\"%s\" minimumUpdatePeriod=\"PT%ui.%03uiS\" minBufferTime=\"PT%ui.%03uiS\" timeShiftBufferDepth=\"%s\" suggestedPresentationDelay=\"PT%ui.%03uiS\" profiles=\"urn:hbbtv:dash:profile:isoff-live:2012, urn:mpeg:dash:profile:isoff-live:2011\" xmlns:xsi=\"http://www.w3.org/2011/XMLSchema-instance\" xsi:schemaLocation=\"urn:mpeg:DASH:schema:MPD:2011 DASH-MPD.xsd\">"


#define NGX_RTMP_DASH_MANIFEST_PERIOD                                          \
    "<Period start=\"PT0S\" id=\"dash\">"


#define NGX_RTMP_DASH_MANIFEST_ADAPTATIONSET_VIDEO                             \
    "<AdaptationSet id=\"1\" startWithSAP=\"1\" segmentAlignment=\"true\" maxWidth=\"%ui\" maxHeight=\"%ui\" maxFrameRate=\"%s\" par=\"%ui:%ui\">"


#define NGX_RTMP_DASH_INBAND_EVENT                                             \
    "<InbandEventStream schemeIdUri=\"urn:scte:scte35:2013:xml\" value=\"1\" />"


#define NGX_RTMP_DASH_MANIFEST_CONTENT_PROTECTION_CENC                         \
    "<ContentProtection cenc:default_KID=\"%02xd%02xd%02xd%02xd-%02xd%02xd-%02xd%02xd-%02xd%02xd-%02xd%02xd%02xd%02xd%02xd%02xd\" schemeIdUri=\"urn:mpeg:dash:mp4protection:2011\" value=\"cenc\"/>"


#define NGX_RTMP_DASH_MANIFEST_CONTENT_PROTECTION_PSSH_CENC                    \
    "<ContentProtection schemeIdUri=\"urn:uuid:1077efec-c0b2-4d02-ace3-3c1e52e2fb4b\"> <cenc:pssh>%V</cenc:pssh></ContentProtection>"


#define NGX_RTMP_DASH_MANIFEST_CONTENT_PROTECTION_PSSH_WDV                     \
    "<ContentProtection schemeIdUri=\"urn:uuid:edef8ba9-79d6-4ace-a3c8-27dcd51d21ed\"><cenc:pssh>%V</cenc:pssh></ContentProtection>"


#define NGX_RTMP_DASH_MANIFEST_CONTENT_PROTECTION_PSSH_MSPR                    \
    "<ContentProtection schemeIdUri=\"urn:uuid:9a04f079-9840-4286-ab92-e65be0885f95\" value=\"MSPR 2.0\"><cenc:pssh>%V</cenc:pssh><mspr:IsEncrypted>1</mspr:IsEncrypted><mspr:IV_Size>8</mspr:IV_Size><mspr:kid>%V</mspr:kid><mspr:pro>%V</mspr:pro></ContentProtection>"


#define NGX_RTMP_DASH_MANIFEST_REPRESENTATION_VIDEO                            \
    "<Representation id=\"%V_H264\" mimeType=\"video/mp4\" codecs=\"avc1.%02uxi%02uxi%02uxi\" width=\"%ui\" height=\"%ui\" frameRate=\"%s\" sar=\"1:1\"  bandwidth=\"%ui\"> <SegmentTemplate presentationTimeOffset=\"0\" timescale=\"1000\" media=\"%V%s$Time$.m4v\" initialization=\"%V%sinit.m4v\"><SegmentTimeline>"


#define NGX_RTMP_DASH_MANIFEST_REPRESENTATION_VARIANT_VIDEO                    \
    "<Representation id=\"%V%V_H264\" mimeType=\"video/mp4\" codecs=\"avc1.%02uxi%02uxi%02uxi\" sar=\"1:1\" "


#define NGX_RTMP_DASH_MANIFEST_VARIANT_ARG                                     \
    " %V"


#define NGX_RTMP_DASH_MANIFEST_VARIANT_ARG_FOOTER                              \
    ">"


#define NGX_RTMP_DASH_MANIFEST_SEGMENTTPL_VARIANT_VIDEO                        \
    "<SegmentTemplate presentationTimeOffset=\"0\" timescale=\"1000\" media=\"%V%V%s$Time$.m4v\" initialization=\"%V%V%sinit.m4v\">xs<SegmentTimeline>"


#define NGX_RTMP_DASH_MANIFEST_REPRESENTATION_VIDEO_FOOTER                     \
    "</SegmentTimeline></SegmentTemplate></Representation>"


#define NGX_RTMP_DASH_MANIFEST_ADAPTATIONSET_VIDEO_FOOTER                      \
    "</AdaptationSet>"


//    "             <S t=\"%uL\" d=\"%uD\"/>"

#define NGX_RTMP_DASH_MANIFEST_TIME                                            \
    "<S t=\"%uD\" d=\"%uD\"/>"


#define NGX_RTMP_DASH_MANIFEST_TIME_WITH_REPETITION                            \
    "<S t=\"%uD\" d=\"%uD\" r=\"%uD\"/>"


#define NGX_RTMP_DASH_MANIFEST_ADAPTATIONSET_AUDIO                             \
    "<AdaptationSet id=\"2\" startWithSAP=\"1\" segmentAlignment=\"true\"> <AudioChannelConfiguration schemeIdUri=\"urn:mpeg:dash:23003:3:audio_channel_configuration:2011\" value=\"1\"/>"


#define NGX_RTMP_DASH_MANIFEST_REPRESENTATION_AUDIO                            \
    "<Representation id=\"%V_AAC\" mimeType=\"audio/mp4\" codecs=\"mp4a.%s\" audioSamplingRate=\"%ui\" bandwidth=\"%ui\"> <SegmentTemplate presentationTimeOffset=\"0\" timescale=\"1000\" media=\"%V%s$Time$.m4a\" initialization=\"%V%sinit.m4a\"><SegmentTimeline>"


#define NGX_RTMP_DASH_MANIFEST_REPRESENTATION_AUDIO_FOOTER                     \
    "</SegmentTimeline> </SegmentTemplate> </Representation>"


#define NGX_RTMP_DASH_MANIFEST_ADAPTATIONSET_AUDIO_FOOTER                      \
    "</AdaptationSet>"


#define NGX_RTMP_DASH_PERIOD_FOOTER                                          \
    "</Period>"


#define NGX_RTMP_DASH_MANIFEST_CLOCK                                           \
    "<UTCTiming schemeIdUri=\"urn:mpeg:dash:utc:%s:2014\" value=\"%V\" />"


#define NGX_RTMP_DASH_MANIFEST_FOOTER                                          \
    "</MPD>"


#endif
