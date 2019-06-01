SET PATH=D:\KEIL5\arm\ARM\ARMCC\Bin;C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v8.0\bin;C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v8.0\libnvvp;D:\Python\Scripts\;D:\Python\;C:\Program Files (x86)\Intel\iCLS Client\;C:\Program Files\Intel\iCLS Client\;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files\Intel\WiFi\bin\;C:\Program Files\Common Files\Intel\WirelessCommon\;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files\Intel\Intel(R) Management Engine Components\DAL;C:\Program Files (x86)\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files\Intel\Intel(R) Management Engine Components\IPT;C:\Program Files\Acer ProShield\;C:\Program Files\Acer ProShield\x86;C:\Users\22187\.dnx\bin;C:\Program Files\Microsoft DNX\Dnvm\;C:\Program Files\Microsoft SQL Server\130\Tools\Binn\;C:\Program Files (x86)\Windows Kits\8.1\Windows Performance Toolkit\;D:\MATLAB\runtime\win64;D:\MATLAB\bin;C:\WINDOWS\system32;C:\WINDOWS;C:\WINDOWS\System32\Wbem;C:\WINDOWS\System32\WindowsPowerShell\v1.0\;C:\Program Files\Microsoft SQL Server\Client SDK\ODBC\110\Tools\Binn\;C:\Program Files (x86)\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\Tools\Binn\;C:\Program Files\Microsoft SQL Server\120\DTS\Binn\;C:\WINDOWS\System32\OpenSSH\;C:\Program Files (x86)\NVIDIA Corporation\PhysX\Common;D:\Git\Git\cmd;D:\Python\Scripts\;D:\Python\;C:\OrCAD\OrCAD_16.6_Lite\OpenAccess\bin\win32\opt;C:\OrCAD\OrCAD_16.6_Lite\tools\pcb\bin;C:\OrCAD\OrCAD_16.6_Lite\tools\fet\bin;C:\OrCAD\OrCAD_16.6_Lite\tools\Capture;C:\OrCAD\OrCAD_16.6_Lite\tools\PSpice;C:\OrCAD\OrCAD_16.6_Lite\tools\specctra\bin;C:\OrCAD\OrCAD_16.6_Lite\tools\bin;C:\Users\22187\AppData\Local\Microsoft\WindowsApps;
SET CPU_TYPE=STM32F103C8
SET CPU_VENDOR=STMicroelectronics
SET UV2_TARGET=LED-DEMO
SET CPU_CLOCK=0x00B71B00
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmAsm" --Via ".\output\startup_stm32f10x_hd._ia"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\main.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_it.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\pid.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\key.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\usart.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\servo.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_gpio.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_rcc.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_dma.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_usart.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\misc.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\stm32f10x_can.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\core_cm3.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmCC" --Via ".\output\system_stm32f10x.__i"
"D:\KEIL5\arm\ARM\ARMCC\Bin\ArmLink" --Via ".\Output\STM32-DEMO.lnp"
"D:\KEIL5\arm\ARM\ARMCC\Bin\fromelf.exe" ".\Output\STM32-DEMO.axf" --i32combined --output ".\Output\STM32-DEMO.hex"
