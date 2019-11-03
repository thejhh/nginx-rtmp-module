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

cd /home/ubuntu/nginx-rtmp-module/ && git pull origin original && cd /root/nginx/nginx-1.16.0/ && ./configure --with-http_ssl_module  --with-http_stub_status_module --with-debug --add-dynamic-module=/home/ubuntu/nginx-rtmp-module && make && make install  && /usr/local/nginx/sbin/nginx -s stop && /usr/local/nginx/sbin/nginx && rm /usr/local/nginx/logs/core || true


curl -v -X POST -T 'master.m3u8' -H "User-Agent: Harmonic" \ "https://p-ep{streamID}.i.akamaientrypoint.net/cmaf/2008614/demo/master.m3u8"


/usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx_high.conf && /usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx_med.conf && /usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx_low.conf && /usr/local/nginx/sbin/nginx -c /usr/local/nginx/conf/nginx.conf