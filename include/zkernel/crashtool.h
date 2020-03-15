#pragma once

namespace ZKERNEL
{
    /**@brief
        开启dmup模式
        开启后，当程序挂掉时，会生成一个dump文件，该文件在temp目录
        文件名格式：死机时间、程序名称 .exe.dmp
        如下
        20150116174802_CrashShare.exe.dmp
    */
    void StartCrashReport();
}