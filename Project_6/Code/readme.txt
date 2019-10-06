使用程式前先使用指令make生成HuffmanTree檔案

輸入./HuffmanTree即可執行程式
主程式main可依照個人需求自訂內容

另外在HuffmanTree.cpp中
TerminalNode的getLChild()及getRChild()和InternalNode的getValue()函式，
原本都是有可能要輸出錯誤訊息的，
但是因為我在HuffmanTree的部分函式中有使用到這三個函式，
若要輸出錯誤訊息的話，輸出版面會稍嫌凌亂，
所以我先使用//把錯誤訊息屏蔽，若要解處的話，把//拿掉即可。

405235035 資工二 王博輝 b121417393@gmail.com
