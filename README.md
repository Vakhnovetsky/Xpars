# Xpars
Редактор экранных форм (мнемосхем) для проприетарной SCADA системы.
Проект был реализован в 2012 году с использованием на тот момент актуальной версии Qt4 в Qt Creator.

Целью проекта был рефакторинг легаси кода с использованием современных библиотек. 

В качестве входных/выходных файлов используются конфигурационные файлы XML формата, которые содержат данные о мнемохемах и объектах управления и сигнализации.
Чтение файлов реализовано посредством класса QDomDocument. Визуализация экранных форм реализована библиотекой QGraphicsScene.
На загруженную мнемосхему можно добавлять, удалять и изменять свойства и параметры объектов при помощи диалоговых окон.  

В 2017 году была добавлена возможность сохранения информации об объектах управления в виде тегов в файл типа cfg для последующей загрузке в OPC сервер.
