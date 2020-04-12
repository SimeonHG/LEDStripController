# Setup

Качете **[LEDServer.ino](https://github.com/SimeonHG/LEDStripController/blob/master/LEDServer/LEDServer.ino "LEDServer.ino")** скрипта на esp8266  през arduino средата. Убедете се, че сте променили **STASSID** и **STAPSK** (намиращи се на 16 и 17 ред в скрипта) на съответно вашите име на мрежа и парола.

Изтеглете **[app-release.apk](https://github.com/SimeonHG/LEDStripController/blob/master/StripApp/app/release/app-release.apk "app-release.apk")** на вашето Аndroid устройство с версия поне **Jelly Bean** (4.1 – 4.3.1)  и го инсталирайте. 
>  Note: Сегашния build работи само за моята мрежа (хардкодната е).  Алтернативно можете да направите ваш build на приложението през **Android Studio**, като смените ip адресите от [EmptyActivity.java](https://github.com/SimeonHG/LEDStripController/blob/master/StripApp/app/src/main/java/com/example/stripapp/EmptyActivity.java "EmptyActivity.java") с желаните от вас. За в бъдеще всеки ще може да си задава и да пази няколко мрежи в приложението.

Уверете се, че и 2те устройства са на една мрежа.
Регистрирайте се в приложението

![](https://i.imgur.com/BAb0G3J.png)

Enjoy!
