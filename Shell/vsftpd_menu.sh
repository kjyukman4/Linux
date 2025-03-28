#!/bin/bash

while :
do
	#clear
	echo "---------------------------"
	echo "vsftpd 시작/중지/재시작"
	echo "---------------------------"
	echo "[1] vsftpd 시작하기"
	echo "[2] vsftpd 중지하기"
	echo "[3] vsftpd 재시작하기"
	echo "[4] 프로그램 종료하기"
	echo "==========================="
	echo -n "메뉴에서 번호를 선택하세요. [1-4] : "
	read choice
	case $choice in
		1) /etc/rc.d/init.d/vsftpd start \
			&& ps ax|grep /usr/sbin/vsftpd|grep -v grep;;
		2) /etc/rc.d/init.d/vsftpd stop;;
		3) /etc/rc.d/init.d/vsftpd restart \
			&& ps ax|grep /usr/sbin/vsftpd|grep -v grep;;
		4) exit 0;;
		*) echo "1에서 4번 중 선택하세요.";;
	esac
done
