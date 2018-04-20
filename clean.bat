@echo off 
for /R %%s in (*~) do (  
del %%s  
)  
for /R %%s in (*.exe) do (  
del %%s  
)  