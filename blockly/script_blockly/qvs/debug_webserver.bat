@echo off
@cd /d %~sdp0
@tskill node 2>nul 1>nul
@node webserver.js
cmd
