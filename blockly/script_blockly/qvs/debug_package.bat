@echo off
@cd /d %~sdp0
@cd ../..
@del script_blockly.blockly
@cd script_blockly
@7z a -tzip -r -y ../script_blockly.blockly . 2>nul 1>nul
@7z l ../script_blockly.blockly
@cd ..
@rmdir /s/q ..\\build\\debug-64bit-msvc\\tools\\ScriptBlockly\\
@mkdir ..\\build\\debug-64bit-msvc\\tools\\ScriptBlockly\\
@copy script_blockly.blockly ..\\build\\debug-64bit-msvc\\tools\\ScriptBlockly
exit
