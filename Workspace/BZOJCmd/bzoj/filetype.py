# -*- coding: utf-8 -*-  
import struct 
# ֧���ļ�����  
# ��16�����ַ�����Ŀ���ǿ���֪���ļ�ͷ�Ƕ����ֽ�  
# �����ļ�ͷ�ĳ��Ȳ�һ��������2�ַ�������8�ַ�  
def typeList():  
	return {  "FFD8FF": "JPEG",  "89504E47": "PNG"}  

# �ֽ���ת16�����ַ���  
def bytes2hex(bytes):  
	num = len(bytes)  
	hexstr = u""  
	for i in range(num):  
		t = u"%x" % bytes[i]  
		if len(t) % 2:  
			hexstr += u"0"
			hexstr += t  
	return hexstr.upper()  

# ��ȡ�ļ�����  
def filetype(filename):  
	binfile = open(filename, 'rb') # ��������ֶ�ȡ  
	tl = typeList()  
	ftype = 'unknown'
	for hcode in tl.keys():  
		numOfBytes = len(hcode) / 2 # ��Ҫ�������ֽ�  
		binfile.seek(0) # ÿ�ζ�ȡ��Ҫ�ص��ļ�ͷ����Ȼ��һֱ�����ȡ  
		hbytes = struct.unpack_from("B"*numOfBytes, binfile.read(numOfBytes)) # һ�� "B"��ʾһ���ֽ�  
		f_hcode = bytes2hex(hbytes)  
		if f_hcode == hcode:  
			ftype = tl[hcode]  
		print hbytes
		break
	binfile.close()  

filetype("1005.cpp")
