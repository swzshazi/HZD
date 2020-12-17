#!/bin/sh

echo "install ..."

rm /home/IEC103
rm /home/LCDConfig.txt
rm /home/SLAVE
rm /home/uapcsys_ver.ini
rm /home/Statistic.txt
rm /home/LogicFuncs.txt
rm /home/LogicEdit.txt
rm /home/103INFO_CN.txt
rm /home/liblogext.so
rm /home/master
rm /home/config.txt
rm /home/setting.txt
rm /home/setting.bak
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

rm -rf /home/wave/pyhost
rm -rf /home/wave/pylcd
rm -rf /home/wave/pylcdlib

tar -zxvf /home/wave/HOST  -C /home/wave/
chmod +x /home/wave/pyhost/master
ln  -s  /home/wave/pyhost/master    /home/master
rm	/home/wave/python3.6/lib/python3.6/idlelib/liblogext.so
mv  /home/wave/pyhost/undo.py  /home/wave/python3.6/lib/python3.6/idlelib/
rm  /home/wave/HOST
mv /home/wave/pyhost/download.sh /home/download.sh
chmod +x /home/download.sh

tar -zxvf /home/wave/MMI -C /home/wave/
mkdir /home/wave/pylcdlib
ln -s /home/wave/pylcd/dlls/libzmq.so.5.2.1   /home/wave/pylcdlib/libzmq.so.5
ln -s /home/wave/pylcd/dlls/libzmq_api.so     /home/wave/pylcdlib/libzmq_api.so
ln -s /home/wave/pylcd/dlls/libai.so         /home/wave/pylcdlib/libai.so
ln -s /home/wave/pylcd/dlls/libdr.so         /home/wave/pylcdlib/libdr.so
ln -s /home/wave/pylcd/dlls/libed.so         /home/wave/pylcdlib/libed.so
ln -s /home/wave/pylcd/dlls/libev.so         /home/wave/pylcdlib/libev.so
ln -s /home/wave/pylcd/dlls/libhzplatform.so /home/wave/pylcdlib/libhzplatform.so
ln -s /home/wave/pylcd/dlls/libwv.so         /home/wave/pylcdlib/libwv.so

mv /home/libhzplatform.so       /home/wave/pylcd/dlls/libhzplatform.so
mv /home/LCDConfig.json         /home/wave/pylcd/LCDConfig.json

rm  /home/wave/MMI
rm  /home/language.txt
rm  /home/startup.sh
echo "install lcd done..."
reboot

