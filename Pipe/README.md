KONU:

  Pipe ve fork yapısı kullanılarak 3x3 matris için kofaktör hesaplanması.

ÖZET:

  Program çalıştırıldığında rastgele 3x3 matris oluşturulup, yine
  rastgele seçilen bir satır ya sutuna göre kofaktör hesaplaması
  yapmaktadır. Ana program(determinant3x3.c) rastgele matrisi
  oluşturduktan sonra satır ya da sutun seçme işlemini yapmak için fork ile
  çocuk process oluşturup satsutsec.c programını çalıştırmaktadır.
  Satsutsec.c programı rastgele seçtiği satır ya da sutunu named pipe ile
  verilen yola yazar. Ana program yazılan değeri pipe’dan okur. Daha sonra
  okunan değere göre determinant işlemleri için kofakhesap.c programını
  fork ile çağırır.
  
  

