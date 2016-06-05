@echo off
RD /S /Q ".\Build"
RD /S /Q ".\Binaries"
RD /S /Q ".\Intermediate"
RD /S /Q ".\Saved"

echo Give a moment for the folders to be deleted...
timeout 5

start MetalHeads.uproject

exit