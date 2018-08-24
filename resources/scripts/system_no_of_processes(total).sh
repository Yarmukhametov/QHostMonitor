#!/bin/sh
#[Name] SYSTEM: # of processes (total)
#[Hint] Params: <MaxLimit>
#[Developer] KS-Soft (www.ks-soft.net)
#[Platform] AIX/BSD/Linux/Solaris
#[Version] 1.3
#[Date] 03.08.2017
#[Start cmd] %Script% %Params%
#[Comment]
#--------------------------------------------------------------------
#Purpose:    Checks how many processes (in total) exist on the system. 
#
#Parameters:
#- MaxLimit:script sets "Bad" status when number of processes is greater
#           than specified limit. 
#
#Tested on :
# - AIX 5.3                 - NetBSD 3.0.1
# - Linux Mandrake 9.1      - FreeBSD 4.5
# - Solaris 9               - OpenBSD 3.9
#--------------------------------------------------------------------
#[History]
# Aug 04, 2017	v 1.3	KS-Soft: macOS support 
# Nov 07, 2006	v 1.2	KS-Soft: NetBSD, OpenBSD support
# Oct 07, 2006	v 1.1	KS-Soft: AIX support
# Feb 01, 2004	v 1.0	KS-Soft: Just released

if [ $# -ge 1 ]
then
  OS=`uname`
  case $OS in
    AIX)    PLIST='ps -A';;
    Linux)  PLIST='ps -ax';;
    Darwin) PLIST='ps -ax';;
    FreeBSD)PLIST='ps -ax';;
    NetBSD) PLIST='ps -ax';;
    OpenBSD)PLIST='ps -ax';;
    SunOS)  PLIST='ps -e';;
    *) echo 'ScriptRes:Unknown:script is not designed for '$OS
       exit;;
  esac
  $PLIST | awk 'BEGIN {count=-1} {count++} END { if (count>'$1') {printf("ScriptRes:Bad:%d\n",count)} else {printf("ScriptRes:Ok:%d\n",count)} }'
else
  echo 'ScriptRes:Unknown:not enough parameters specified'
fi
