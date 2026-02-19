# TinyML-Dinamik-Tensor-Yonetimi

Bu proje, kısıtlı donanım kaynaklarına (RAM/CPU) sahip uç cihazlar (Edge Devices) için optimize edilmiş bir dinamik tensör yönetim sistemini simüle eder. Proje kapsamında C dilindeki `union` yapısı kullanılarak bellek verimliliği sağlanmış ve ondalıklı veriler (Float32), 8-bit tam sayılara (Int8) nicemlenmiştir.


# Temel Özellikler
  
Dinamik Bellek Yönetimi: `malloc` fonksiyonu kullanılarak çalışma zamanında (runtime) esnek veri boyutu yönetimi sağlanmıştır.

Bellek Tasarrufu (Union Re-interpretation): `union` yapısı kullanılarak farklı veri tipi işaretçileri (`float\*` ve `int8\_t\*`) aynı fiziksel bellek adresini paylaşacak şekilde kurgulanmıştır. Bu teknik, veri dönüşümü sırasında ekstra RAM kullanımını %50 oranında azaltır.

8-bit Nicemleme (Quantization): Model boyutunu ve işlem yükünü %75 oranında küçültmek amacıyla Float32 veriler, belirlenen bir ölçek (scale) değeri ile Int8 formatına dönüştürülür.

Doygunluk Aritmetiği (Clipping): Veri dönüşümü sırasında 8-bit sınırlarının (-128, 127) aşılması durumunda "Integer Overflow" hatalarını engellemek için sabitleme (clipping) mantığı uygulanmıştır.


# Teknik Analiz ve Hata Ayıklama (Debugging)

Proje geliştirme sürecinde aşağıdaki teknik analiz adımları uygulanmıştır:
1. Adres Doğrulama: `printf("%p")` format belirleyicisi kullanılarak bellek adresleri takip edilmiştir. Union içerisindeki float ve integer işaretçilerinin tıpatıp aynı adresi göstermesi, bellek optimizasyonunun başarısını kanıtlamaktadır.
2. Matris ve Bellek Yönetimi: Dinamik bellek tahsisi sırasında `sizeof` operatörü ile platform bağımsız veri genişliği korunmuş ve işlem sonunda `free()` fonksiyonu ile bellek sızıntıları (memory leak) önlenmiştir.
3. Algoritma Kararlılığı: Giriş verisi 100.0 olduğunda, hesaplanan değer 200 olsa dahi sistemin bunu otomatik olarak int8 üst sınırı olan 127'de sabitlediği doğrulanmıştır.


# Kurulum ve Çalıştırma

Kod standart C99 uyumludur ve GCC derleyicisi olan tüm IDE'lerde (OnlineGDB, Dev-C++, Code::Blocks vb.) çalıştırılabilir.


# Derleme ve Çalıştırma Adımları:

1. `dinamik_tensor_projesi.c` dosyasını indirin.
2. Terminal veya IDE üzerinden derleyin.
3. Çıktı ekranındaki adres eşleşmelerini ve nicemleme sonuçlarını inceleyin.


```bash
gcc dinamik_tensor_projesi.c -o tiny_ml_test
./tiny_ml_test


