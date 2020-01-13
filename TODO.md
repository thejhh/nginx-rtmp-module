## TODO

- doc // OK 
- need re-upstream // wait response
- rewritte the variant code for dash, using memory ?

- add option emsg_timestamp_hack


- test common encryption code (OK clearkey, Widevine both on chrome/firefox!)
- need to write some doc about cenc/drm implem
- refacto code for writing content protection in manifest // OK
- clarify the use of %V in ngx_printf // OK
- refacto code for init / kid // OK
- correct pssh in manifest // OK
- add pssh / cenc in variant mpd // OK
- add real base64 encrypt pssh data // OK 
- add support for sub sample encryption //OK
- add sig for wdv //OK
- add struct for drm info // OK
- add pssh in init file for wdv // OK
- add msplayready support // OK need pssh in init file 
./configure --with-http_ssl_module  --with-http_stub_status_module --with-debug --add-dynamic-module=/home/ubuntu/nginx-rtmp-module
make
make install
/usr/local/nginx/sbin/nginx -s stop
/usr/local/nginx/sbin/nginx

./configure --with-http_ssl_module  --with-http_stub_status_module --with-debug --add-module=/opt/nginx-rtmp-module && make && make install

cd /home/ubuntu/nginx-rtmp-module/ && git pull origin original && cd /root/nginx/nginx-1.16.0/ && ./configure --with-http_ssl_module  --with-http_stub_status_module --with-debug --add-module=/home/ubuntu/nginx-rtmp-module --add-module=/home/ubuntu/njs/nginx && make && make install  && /usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx.conf -s stop && /usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx.conf && rm /usr/local/nginx/logs/core || true


/usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx_low.conf && /usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx_med.conf && /usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx_high.conf && /usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx.conf
curl -v -X POST -T 'master.m3u8' -H "User-Agent: Harmonic" \ "https://p-ep{streamID}.i.akamaientrypoint.net/cmaf/2008614/demo/master.m3u8"





exec ffmpeg -i rtmp://localhost:1936/$app/$name -map_metadata -1 -x264-params "nal-hrd=cbr" -break_non_keyframes 1 -loglevel 0 -async 1 -vsync 1 -vcodec copy -vprofile main -c:v libx264 -x264-params "keyint=30:no-scenecut" -acodec copy  -tune zerolatency -preset veryfast -crf 28 -profile:v baseline -level 3.0 -s 360x640 -b:v 400K -b:a 64k -f flv rtmp://localhost:1936/dash/$name_high

ffmpeg -i rtmp://localhost:1935/$app/$name -loglevel 0 -r 30 -async 1 -vsync 1 -map_metadata -1 -break_non_keyframes 1 -c:v libx264 -x264opts no-scenecut -c:a aac -crf 23 -profile:v baseline -level 3.0 -tune zerolatency -preset veryfast -s 368x640 -b:v 400K -maxrate 400K -bufsize 2400K -g 60 -ab 64K -ac 1 -f flv rtmp://localhost:1936/dash/$name_high;

ffmpeg -i rtmp://localhost:1935/$app/$name -loglevel 0 -r 30 -async 1 -vsync 1 -map_metadata -1 -break_non_keyframes 1 -c:v libx264 -x264opts no-scenecut -c:a aac -crf 23 -profile:v baseline -level 3.0 -tune zerolatency -preset veryfast -s 368x640 -b:v 240k -maxrate 240K -bufsize 1200K -g 60 -ab 64K -ac 1 -f flv rtmp://localhost:1936/dash/$name_med;

ffmpeg -i rtmp://localhost:1935/$app/$name -loglevel 0 -r 30 -async 1 -vsync 1 -map_metadata -1 -break_non_keyframes 1 -c:v libx264 -x264opts no-scenecut -c:a aac -crf 23 -profile:v baseline -level 3.0 -tune zerolatency -preset veryfast -s 368x640 -b:v 160k -maxrate 160K -bufsize 600K -g 60 -ab 64K -ac 1 -f flv rtmp://localhost:1938/dash/$name_low;

exec ffmpeg -i rtmp://localhost:1935/$app/$name -break_non_keyframes 1 -loglevel 0 -map_metadata -1 -c:v libx264 -c:a aac -profile:v baseline -level 3.0 -async 1 -vsync 1 -tune zerolatency -preset veryfast -f flv rtmp://localhost:1936/live/$name -f flv rtmp://localhost:1937/$app/$name -f flv rtmp://localhost:1938/$app/$name;

exec ffmpeg -i rtmp://localhost:1935/$app/$name -break_non_keyframes 1 -loglevel 0 -map_metadata -1 -vcodec copy -acodec copy -async 1 -vsync 1 -tune zerolatency -preset veryfast -f flv rtmp://localhost:1936/live/$name -f flv rtmp://localhost:1937/$app/$name -f flv rtmp://localhost:1938/$app/$name;

exec ffmpeg -i rtmp://localhost:1935/live/testtest30 -break_non_keyframes 1 -loglevel 48 -map_metadata -1 -vcodec copy -acodec copy -async 1 -vsync 1 -tune zerolatency -preset veryfast \
-f flv rtmp://localhost:1936/live/testtest30 \
-f flv rtmp://localhost:1937/live/testtest30 \
-f flv rtmp://localhost:1938/live/testtest30;



exec ffmpeg -i rtmp://localhost:1935/$app/$name -map_metadata -1 -x264-params "nal-hrd=cbr" -break_non_keyframes 1 -loglevel 0 -async 1 -vsync 1 -vcodec copy -vprofile main -c:v libx264 -x264opts keyint=30:no-scenecut -acodec copy  -tune zerolatency -preset veryfast -crf 28 -profile:v baseline -level 3.0 -s 360x640 -b:v 400K -b:a 64k -f flv rtmp://localhost:1936/dash/$name_high;

exec ffmpeg -i rtmp://localhost:1935/$app/$name -map_metadata -1 -x264-params "nal-hrd=cbr" -break_non_keyframes 1 -loglevel 0 -async 1 -vsync 1 -vcodec libx264 -vprofile main -c:v libx264 -x264opts keyint=30:no-scenecut -acodec aac  -tune zerolatency -preset veryfast -crf 28 -profile:v baseline -level 3.0 -s 360x640 -b:v 240k -b:a 64k -f flv rtmp://localhost:1937/dash/$name_med;

exec ffmpeg -i rtmp://localhost:1938/$app/$name -map_metadata -1 -x264-params "nal-hrd=cbr" -break_non_keyframes 1 -loglevel 0 -async 1 -vsync 1 -vcodec libx264 -vprofile main -c:v libx264 -x264opts keyint=30:no-scenecut -acodec aac  -tune zerolatency -preset veryfast -crf 28 -profile:v baseline -level 3.0 -s 360x640 -b:v 160K -b:a 64k -f flv rtmp://localhost:1938/dash/$name_low;


exec ffmpeg -i rtmp://localhost:1935/$app/$name -loglevel 0 -r 30 -async 1 -vsync 1 -map_metadata -1 -break_non_keyframes 1 -c:v libx264 -x264opts no-scenecut -c:a aac -crf 23 -profile:v baseline -level 3.0 -tune zerolatency -preset veryfast -s 368x640 -b:v 400K -maxrate 400K -bufsize 2400K -g 60 -ab 64K -ac 1 -f flv rtmp://localhost:1936/dash/$name_high;

exec ffmpeg -i rtmp://localhost:1935/$app/$name -loglevel 0 -r 30 -async 1 -vsync 1 -map_metadata -1 -break_non_keyframes 1 -c:v libx264 -x264opts no-scenecut -c:a aac -crf 23 -profile:v baseline -level 3.0 -tune zerolatency -preset veryfast -s 368x640 -b:v 240k -maxrate 240K -bufsize 1200K -g 60 -ab 64K -ac 1 -f flv rtmp://localhost:1936/dash/$name_med;

exec ffmpeg -i rtmp://localhost:1935/$app/$name -loglevel 0 -r 30 -async 1 -vsync 1 -map_metadata -1 -break_non_keyframes 1 -c:v libx264 -x264opts no-scenecut -c:a aac -crf 23 -profile:v baseline -level 3.0 -tune zerolatency -preset veryfast -s 368x640 -b:v 160k -maxrate 160K -bufsize 600K -g 60 -ab 64K -ac 1 -f flv rtmp://localhost:1938/dash/$name_low;