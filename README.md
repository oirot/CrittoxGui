# CrittoxGui
 This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


Gui app to crypt and encrypt text files
This programm depends on wxWidgets 3.0.2 and Openssl 1.0.2h
You can find them at:
https://www.wxwidgets.org/downloads/
https://www.openssl.org/source/

To build it open a terminal and cd into CrittoxGui main directory. Give "mkdir obj; make". That's all.

This is an app that aims to crypt and decrypt text files. It can handle only ascii printable character (from '\032' to '\126').
You have to insert the file you wanto to encrypt in the "File to process path" and where you want to save the encrypted text in "Processed file path". At the right and center it has a radio button labeled whith "Way round" you have to chose one of them to crypt and the other to decrypt the same file. When done the start button should be enabled, click on it to perform the task.
It has two main modes to operate on files.
The simple mode perforsm only a shift in the alphabet order using the key/psw you immitted in the "Password" field or you wrote in the first line of a "*.txt" file. The file can be used switching on the "by file" radio button above the "Password" text.
The advanced mode tries to gain more security by adding pseudorandom character to the text files in order to compromise a statistical analysis of the files. It saves the position of the pseudorandom character in a file "*.syn". While decrypting a file that has been encrypted using the advanced mode you have to select the previus generated "*.syn" file (you can share it via unsicure channel because it is encrypted by binary XOR with the hash (sha512) of the key/psw) in the "Synod file path" field that is enabled by clicking on the "Advanced" switch. The "Block size:" parameter told the aproximatively lenght of the encrypted file in advanced mode and give information to the app about the number character to add to the encrypted file.
In simple mode you need only set the file fields ("File to process path", "Processed file path") and give a key/psw (of lenght >= 5) and then the start button should be enabled. In the advanced one you need also to entry the "Synod file path" field and specificate if you want to encrypt or decrypt the file using the radio buttons in down and right labeled whit "Operation".
Hope you enjoy this!


Contact info:
email: vittorio.aiello98@gmail.com
