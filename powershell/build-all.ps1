# USER DEFINED
$le = "D:\Games\SteamLibrary\steamapps\common\Skyrim"
$outDir = "D:\Games\SteamLibrary\steamapps\common\Skyrim\Data"


# GRAB DIRECTORIES
$leSrc = $le + "\Data\Scripts\Source"
$usrSrc = (Get-Location)
$papyrus = $le + "\Papyrus Compiler\PapyrusCompiler.exe"
$flags = $leSrc + "\TESV_Papyrus_Flags.flg"


# COMPILE PAPYRUS SCRIPTS
& "$papyrus" "$usrSrc\Scripts\Source" -f="$flags" -i="$leSrc;$usrSrc\Scripts\Source" -o="$outDir\Scripts" -a