#!/bin/bash

echo 스크립트명 : $0
echo 전체 아규먼트 : $*
echo 첫 번째 아규먼트 : $1
echo 두 번째 아규먼트 : $2
echo 전체 아규먼트 수 : $#
oldargs=$*
set CentOS Fedora Ubuntu
echo 전체 파라미터 : $*
echo 전체 위치 파라미터 $#
echo "첫 번째 위치 파라미터 : $1"
set $(date) # 위치 파라미터 재설정
echo 오늘은 $2 $3 $1
echo "\$oldargs : $oldargs"
set $oldargs
echo $1 $2 $3
