# Library

Документация за информационна система **„Библиотека“**<br>
Проектът е разработена информационна система за библиотека, която съдържа информация за определен набор от книги, техния рейтинг, заглавие, автор, ключови думи, жанр, дата на издаване. За работа с програмата се изисква наличието на файл, в който да могат да се запишат и четат направените промени. При неналичието на такъв, няма как да се продължи работа със системата. В системата има два вида потребители – клиенти и админи.<br>

**Всеки вид потребител има правото да:**

1. Показва информация за всички книги.
2. Да търси информация за избрана книга (по идентификационен номер).
3. Да търси книга по ключова дума, заглавие или автор.
4. Да сортира книгите по заглавие, автор, година на издаването или рейтинг както възходящо, така и низходящо.
5. Отваря файл.
6. Затваря файл.
7. Запазва файл.
8. Запазва файл като нов.
9. Извиква опцията help, която дава информация относно други опции на системата.<br>

**Способностите на админа:**

При първоначално включване на системата, винаги има един регистриран админ с име *admin* и парола *i<3c++*. 

Всеки админ има право да:

1. *Добавя нов потребител* – при добавянето на нов потребител се иска информация за вида на потребителя (админ или не), потребителско име (проверява се дали то е уникално) и парола. Потребителското име не може да съдържа спейсове и трябва да е с дължина поне 1. При предоставянето на такова се прави проверка дали такова име вече съществува, ако не - създава се новият потребител. Паролата не трябва да започва или завършва със спейс и трябва да има дължина поне 1, като може да съдържа букви (малки и големи), цифри и спейсове.
2. *Премахва потребител* – при премахването на потребител се иска потребителското име на потребителя.
3. *Добавяне на книга* – при добавянето на книга се иска информация за заглавието, автора и жанра на книгата, рейтинга, както и за годината на публикация. Заглавието, авторът и жанрът на книгата не трябва да започват или завършват със спейс и могат да съдържат единствено букви и спейс. Дължината на всяко едно трябва да е поне една буква. Рейтингът трябва да е цяло число между 0 и 5, а годината на издаване трябва да е по-голяма от 0 и по-малка от настоящата.
4. *Премахване на книга* – при премахване на книга се иска идентификационния номер на книгата, която трябва да се премахне.
5. *Добавяне на ключови думи към дадена книга* – при добавянето на ключова дума се изисква идентификационен номер на книгата и се добавят ключови думи, докато не се напише exit. Всяка дума не трябва да започва и завършва със спейс и не трябва да съдържа такъв.
6. *Добавяне на описание към книга* – при добавяне на описание към книга се изисква идентификационен номер на книгата и се добавя предоставеното описание, като то не трябва да почва и завършва със спейс.<br>

**Всеки потребител, който не е админ, има право да:**

1. *Дава оценка на дадена книга* – при даването на оценка се иска идентификационния номер на книгата. Веднъж гласувал за тази книга, потребителят няма как да гласува втори път. Новият вот се добавя към настоящия рейтинг и се смята средноаритметично. Вотът трябва да е цяло число между 0 и 5.

Направените промени могат да се запишат в бинарен файл. При стартиране на програмата се изисква име на файл, за да може да се отвори дадения файл и да се работи с данните от него. Ако след работа с програмата, даденият файл не бъде запазен, то при ново стартиране ще се върнат първоначалните данни.
