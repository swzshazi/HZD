#!/bin/sh

echo "install ..."

rm /home/download.so
rm /home/main.py
rm /home/start.sh
rm /home/config.txt
rm /home/setting.txt
rm /home/setting.bak
rm /home/SLAVE
rm /home/IEC103
rm /home/runlog1.txt
rm /home/version.txt
rm /home/IEC61850
rm /home/PCSXXX.txt
rm /home/PCSxxx.txt
rm /home/master*
rm /home/wave/python_setup.sh
rm /home/wave/python3.6.tar.gz
rm /home/wave/start.sh
rm /home/log1.txt
rm /home/clear_sram_hex_log.txt
rm /home/clear_sram_log.txt

echo -e welcome to use hz6000 > /etc/issue.net
echo -e welcome to use hz6000 > /etc/issue

rm -rf /home/wave/pyhost
rm -rf /home/wave/pylcd


tar -zxvf /home/wave/HOST  -C /home/wave/
chmod +x /home/wave/pyhost/main.sh
ln  -s  /home/wave/pyhost/main.sh    /home/master
chmod +x  /home/wave/pyhost/rcS
mv  /home/wave/pyhost/rcS        /etc/init.d/rcS
rm	/home/wave/python3.6/lib/python3.6/idlelib/liblogext.so
mv  /home/wave/pyhost/undo.py  /home/wave/python3.6/lib/python3.6/idlelib/
rm  /home/wave/HOST
mv /home/wave/pyhost/download.sh /home/download.sh
chmod +x /home/download.sh

tar -zxvf /home/wave/MMI -C /home/wave/
rm -rf /usr/lib/*
ln -s /home/wave/pylcd/dlls/libzmq.so.5.2.1   /usr/lib/libzmq.so.5
ln -s /home/wave/pylcd/dlls/libzmq_api.so     /usr/lib/libzmq_api.so
ln -s /home/wave/pylcd/dlls/libai.so         /usr/lib/libai.so
ln -s /home/wave/pylcd/dlls/libdr.so         /usr/lib/libdr.so
ln -s /home/wave/pylcd/dlls/libed.so         /usr/lib/libed.so
ln -s /home/wave/pylcd/dlls/libev.so         /usr/lib/libev.so
ln -s /home/wave/pylcd/dlls/libhzplatform.so /usr/lib/libhzplatform.so
ln -s /home/wave/pylcd/dlls/libwv.so         /usr/lib/libwv.so

rm  /home/wave/MMI
mv  /home/libhzplatform.so     /home/wave/pylcd/dlls/
mv  /home/LCDConfig.json     /home/wave/pylcd/LCDConfig.json
rm  /home/LCDConfig.txt
rm  /home/MMI
rm  /home/Statistic.txt
rm  /home/LogicFuncs.txt
rm  /home/LogicEdit.txt
rm  /home/language.txt
rm  /home/103INFO_CN.txt
rm  /home/uapcsys_ver.ini
rm  /home/startup.sh
echo "install lcd done..."
reboot

