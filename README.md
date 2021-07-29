# NGINX-based Media Streaming Server

## nginx-rtmp-module (dash enhanced version)

Forked (again) from [sergey-dryabzhinsky/nginx-rtmp-module](https://github.com/sergey-dryabzhinsky/nginx-rtmp-module) which was the most up to date versio,
and merged dash enhanced changes from [chetandhembre/nginx-rtmp-module](https://github.com/chetandhembre/nginx-rtmp-module).

Notable new features :

 - add the possibility to make adaptative streaming (show below configuration, using ffmpeg to trancode in 3 variants, and produce one manifest).
   note the "max" flag which indicate which representation should have max witdh and height and so use it to create the variant manifest.
   you can also use any encoder to directly push the variant.
 - add the support of using repetition in manifest to shorten them (option dash_repetition) (thanks to Streamroot)
 - add the support of common-encryption; currently working DRM are ClearKey/Widevine/Playready (see specific doc [here](DRM.md))
 - add the support of ad insertion break event, from rtmp AMF message to dash (InbandEvent in manifest and emsg box in mp4 fragment, see doc [here](DAI.md))


See original doc here for full list of options.

```
  rtmp {
    server {
    listen 1935;
   
    application ingest {
      live on;
      exec /usr/bin/ffmpeg -i rtmp://localhost/$app/$name \
           -c:a libfdk_aac -b:a 64k -c:v libx264 -preset fast -profile:v baseline -vsync cfr -s 1024x576 -b:v 1024K -bufsize 1024k \
           -f flv rtmp://localhost/dash/$name_hi \
           -c:a libfdk_aac -b:a 64k -c:v libx264 -preset fast -profile:v baseline -vsync cfr -s 640x360 -b:v 832K -bufsize 832k \
           -f flv rtmp://localhost/dash/$name_med \
           -c:a libfdk_aac -b:a 64k -c:v libx264 -preset fast -profile:v baseline -vsync cfr -s 320x180 -b:v 256K -bufsize 256k \
           -f flv rtmp://localhost/dash/$name_low
    }
      
    application dash {
      live on;
      dash on;
      dash_nested on; 
      dash_repetition on;
      dash_path /dev/shm/dash;
      dash_fragment 4; # 4 second is generaly a good choice for live
      dash_playlist_length 120; # keep 120s of tail
      dash_cleanup on;
      dash_variant _low bandwidth="256000" width="320" height="180";
      dash_variant _med bandwidth="832000" width="640" height="360";
      dash_variant _hi bandwidth="1024000" width="1024" height="576" max;
    }
  }

   server {
      listen 443 ssl;
      location / {
        root /var/www;
        add_header Cache-Control no-cache;
        add_header 'Access-Control-Allow-Origin' '*';
      }
      location /dash/live/index.mpd {
        alias /dev/shm/dash/live/index.mpd;
        add_header 'Access-Control-Allow-Origin' '*';
        add_header Cache-Control 'public, max-age=0, s-maxage=2';
      }
      location /dash/live {
        alias /dev/shm/dash/live;
        add_header 'Access-Control-Allow-Origin' '*';
        add_header Cache-Control 'public, max-age=600, s-maxage=600';
      }

      server_name live.site.net;
      ssl_certificate /etc/letsencrypt/live/live.site.net/fullchain.pem;
      ssl_certificate_key /etc/letsencrypt/live/live.sit.net/privkey.pem;

    }
}
```

## nginx-rtmp-module

### Project blog

  http://nginx-rtmp.blogspot.com

### Documentation

* [Home](doc/README.md)
* [Control module](doc/control_modul.md)
* [Debug log](doc/debug_log.md)
* [Directives](doc/directives.md)
* [Examples](doc/examples.md)
* [Exec wrapper in bash](doc/exec_wrapper_in_bash.md)
* [FAQ](doc/faq.md)
* [Getting number of subscribers](doc/getting_number_of_subscribers.md)
* [Getting started with nginx rtmp](doc/getting_started.md)
* [Installing in Gentoo](doc/installing_in_gentoo.md)
* [Installing on Ubuntu using PPAs](doc/installing_ubuntu_using_ppas.md)
* [Tutorial](doc/tutorial.md)

*Source: https://github.com/arut/nginx-rtmp-module/wiki*

* [Latest updates](doc/README.md#updates)

### Google group

  https://groups.google.com/group/nginx-rtmp

  https://groups.google.com/group/nginx-rtmp-ru (Russian)

### Donation page (Paypal etc)

  http://arut.github.com/nginx-rtmp-module/

### Features

* RTMP/HLS/MPEG-DASH live streaming

* RTMP Video on demand FLV/MP4,
  playing from local filesystem or HTTP

* Stream relay support for distributed
  streaming: push & pull models

* Recording streams in multiple FLVs

* H264/AAC support

* Online transcoding with FFmpeg

* HTTP callbacks (publish/play/record/update etc)

* Running external programs on certain events (exec)

* HTTP control module for recording audio/video and dropping clients

* Advanced buffering techniques
  to keep memory allocations at a minimum
  level for faster streaming and low
  memory footprint

* Proved to work with Wirecast, FMS, Wowza,
  JWPlayer, FlowPlayer, StrobeMediaPlayback,
  ffmpeg, avconv, rtmpdump, flvstreamer
  and many more

* Statistics in XML/XSL in machine- & human-
  readable form

* Linux/FreeBSD/MacOS/Windows

### Build

cd to NGINX source directory & run this:

    ./configure --add-module=/path/to/nginx-rtmp-module
    make
    make install

Several versions of nginx (1.3.14 - 1.5.0) require http_ssl_module to be
added as well:

    ./configure --add-module=/path/to/nginx-rtmp-module --with-http_ssl_module

For building debug version of nginx add `--with-debug`

    ./configure --add-module=/path/to-nginx/rtmp-module --with-debug

[Read more about debug log](https://github.com/arut/nginx-rtmp-module/wiki/Debug-log)

### Contributing and Branch Policy

The "dev" branch is the one where all contributions will be merged before reaching "master".
If you plan to propose a patch, please commit into the "dev" branch or its own feature branch.
Direct commit to "master" are not permitted.

### Windows limitations

Windows support is limited. These features are not supported

* execs
* static pulls
* auto_push

### RTMP URL format

    rtmp://rtmp.example.com/app[/name]

app -  should match one of application {}
         blocks in config

name - interpreted by each application
         can be empty


### Multi-worker live streaming

This NGINX-RTMP module does not support multi-worker live
streaming. While this feature can be enabled through rtmp_auto_push on|off directive, it is ill advised because it is incompatible with NGINX versions starting 1.7.2 and up, there for it should not be used.


### Example nginx.conf

    rtmp {

        server {

            listen 1935;

            chunk_size 4000;

            # TV mode: one publisher, many subscribers
            application mytv {

                # enable live streaming
                live on;

                # record first 1K of stream
                record all;
                record_path /tmp/av;
                record_max_size 1K;

                # append current timestamp to each flv
                record_unique on;

                # publish only from localhost
                allow publish 127.0.0.1;
                deny publish all;

                #allow play all;
            }

            # Transcoding (ffmpeg needed)
            application big {
                live on;

                # On every published stream run this command (ffmpeg)
                # with substitutions: $app/${app}, $name/${name} for application & stream name.
                #
                # This ffmpeg call receives stream from this application &
                # reduces the resolution down to 32x32. The stream is the published to
                # 'small' application (see below) under the same name.
                #
                # ffmpeg can do anything with the stream like video/audio
                # transcoding, resizing, altering container/codec params etc
                #
                # Multiple exec lines can be specified.

                exec ffmpeg -re -i rtmp://localhost:1935/$app/$name -vcodec flv -acodec copy -s 32x32
                            -f flv rtmp://localhost:1935/small/${name};
            }

            application small {
                live on;
                # Video with reduced resolution comes here from ffmpeg
            }

            application webcam {
                live on;

                # Stream from local webcam
                exec_static ffmpeg -f video4linux2 -i /dev/video0 -c:v libx264 -an
                                   -f flv rtmp://localhost:1935/webcam/mystream;
            }

            application mypush {
                live on;

                # Every stream published here
                # is automatically pushed to
                # these two machines
                push rtmp1.example.com;
                push rtmp2.example.com:1934;
            }

            application mypull {
                live on;

                # Pull all streams from remote machine
                # and play locally
                pull rtmp://rtmp3.example.com pageUrl=www.example.com/index.html;
            }

            application mystaticpull {
                live on;

                # Static pull is started at nginx start
                pull rtmp://rtmp4.example.com pageUrl=www.example.com/index.html name=mystream static;
            }

            # video on demand
            application vod {
                play /var/flvs;
            }

            application vod2 {
                play /var/mp4s;
            }

            # Many publishers, many subscribers
            # no checks, no recording
            application videochat {

                live on;

                # The following notifications receive all
                # the session variables as well as
                # particular call arguments in HTTP POST
                # request

                # Make HTTP request & use HTTP retcode
                # to decide whether to allow publishing
                # from this connection or not
                on_publish http://localhost:8080/publish;

                # Same with playing
                on_play http://localhost:8080/play;

                # Publish/play end (repeats on disconnect)
                on_done http://localhost:8080/done;

                # All above mentioned notifications receive
                # standard connect() arguments as well as
                # play/publish ones. If any arguments are sent
                # with GET-style syntax to play & publish
                # these are also included.
                # Example URL:
                #   rtmp://localhost/myapp/mystream?a=b&c=d

                # record 10 video keyframes (no audio) every 2 minutes
                record keyframes;
                record_path /tmp/vc;
                record_max_frames 10;
                record_interval 2m;

                # Async notify about an flv recorded
                on_record_done http://localhost:8080/record_done;

            }


            # HLS

            # For HLS to work please create a directory in tmpfs (/tmp/hls here)
            # for the fragments. The directory contents is served via HTTP (see
            # http{} section in config)
            #
            # Incoming stream must be in H264/AAC. For iPhones use baseline H264
            # profile (see ffmpeg example).
            # This example creates RTMP stream from movie ready for HLS:
            #
            # ffmpeg -loglevel verbose -re -i movie.avi  -vcodec libx264
            #    -vprofile baseline -acodec libmp3lame -ar 44100 -ac 1
            #    -f flv rtmp://localhost:1935/hls/movie
            #
            # If you need to transcode live stream use 'exec' feature.
            #
            application hls {
                live on;
                hls on;
                hls_path /tmp/hls;
            }

            # MPEG-DASH is similar to HLS

            application dash {
                live on;
                dash on;
                dash_path /tmp/dash;
            }
        }

