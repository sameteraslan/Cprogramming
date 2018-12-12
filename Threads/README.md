Konu
  C programlama dilinde thread ve named pipe kullanılarak dosyadan
  okunan sayılar üzerinde işlem yapılması.

Özet
  Sistemde “numbers.txt” dosyası içerisinde satırlara sayılar yazılmıştır. 
  Bu sayılarla x + y + z = sonuc işlemi yapılacaktır. Ana
  programın(xyztotalizer.c) başlangıcında kullanıcıdan kaç satır okuma
  yapılması istenmektedir. Kullanıcının gireceği sayı 3 ve 3’ün katı olmak
  zorundadır. Ana programda tasarlanan yapıya göre kullanıcı sayı girdikten
  sonra ilk olarak X threadi çalışır. Bu thread named pipe yapısı ile sisteme
  kendinin X threadi olduğunu belirtecek ve kaçıncı sayının okunması
  gerektiğini bildirecek 2 elemanlı integer matris yazar. Daha sonra yazılan
  martis alt programdan(numberreader.c) okunur ve satır bulunup okunur
  tekrar named pipe’a yazılır. Yazılan değeri X threadi okur. Daha sonra aynı
  şekilde Y threadi çalışır. 3. olarak z threadi çalışmaktadır. X ve Y threadleri
  gibi aynı işlemleri yaptıktan sonra x + y + z = sonuc işlemini ekrana
  yazdırır.
