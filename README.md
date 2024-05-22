<h1>Лабы по Операционным системам<br></h1>
<h2>lab1: Gtk4.0+ C Linux<br></h2>
  <p>Три задачи: <ol>
     <li>Два текстовых поля, кнопка. По кнопке из одного поля по функции добавляется значение в другое.</li>
    <img src="https://github.com/SynI20N/IT/blob/systems/lab1/images/task1.png">
     <li>Два поля, реагирующих на вход в них мыши сменой текста на "пришел-ушел".</li>
    <img src="https://github.com/SynI20N/IT/blob/systems/lab1/images/task2.png">
     <li>Все окно реагирует на перемещение мышки сменой цвета с красного на зеленый.</li>
    <img src="https://github.com/SynI20N/IT/blob/systems/lab1/images/task3.png">
    </ol>
    Запуск: <code>cd lab1 && ./task1.out && ./task2.out && ./task3.out</code>
  </p>
<h2>lab2: CLR C++ Winforms Windows 10<br></h2>
  <p>Задача: Вывести информацию по дискам (свободное и занятое место). Динамически обновлять информацию по дискам. <br>
    <p>До вставки флешки:</p>
    <img src="https://github.com/SynI20N/IT/blob/systems/lab2/Images/drives.PNG">
    <p>После вставки флешки:</p>
    <img src="https://github.com/SynI20N/IT/blob/systems/lab2/Images/drives_upd.PNG">
    Запуск: <code>.\lab2\x64\Debug\FileSystem.exe</code>
  </p>
<h2>lab3: CLR C++ Winforms Windows 10<br></h2>
  <p>Задача: Написать аналог файлового менеджера. Функции: выбрать папку, выбрать файл, переместить, переименовать, удалить, копировать.<br>
    <p>Бвзовый вид приложения:</p>
    <img src="https://github.com/SynI20N/IT/blob/systems/lab3/images/manager.png">
    <p>Приложение в работе:</p>
    <img src="https://github.com/SynI20N/IT/blob/systems/lab3/images/manager_action.png">
    Запуск: <code>.\lab3\x64\Debug\FileManager.exe</code>
  </p>
<h2>lab4: CLR C++ Winforms Windows 10<br></h2>
  <p>Задача: Создать форму, где можно управлять двумя потоками (стартовать, ставить на паузу, менять приоритет).<br>
    <p>Каждый поток считает от нуля в бесконечном цикле и выводит эти значения в соответствующий бокс</p>
    <p>Приложение в работе:</p>
    <img src="https://github.com/SynI20N/IT/blob/systems/lab4/images/threads.gif">
    Запуск: <code>.\lab4\x64\Debug\lab4.exe</code>
  </p>
<h2>lab5: Gtk4.0+ C Linux<br></h2>
  <p>Задача: создать динамическую библиотеку, создать программу в которой динамически подгружается эта библиотека.<br>
    <p>В библиотеке должен находится код, который запускает форму / интерфейс.</p>
    <p>Библиотека libform.so, код запуска driver </p>
    Запуск: <code>./lab5/driver</code>
  </p>
<h2>lab6: C Win32 Windows10</h2>
  <p>Задача: Создать форму, в которой динамически будут выводится все окна, открытые в системе (в том числе и скрытые).<br>
    <p>В форме также присутствует кнопка для изменения размера всех окон через WinApi функцию SetWindowPos</p>
    <p>Дополнительно программа создает дочернее окно в WinMain с помощью функции CreateWindow - ChildWindow</p>
    <p>Приложение в работе:</p>
    <img src="https://github.com/SynI20N/IT/blob/systems/lab6/images/1.png">
    <img src="https://github.com/SynI20N/IT/blob/systems/lab6/images/2.png">
    <img src="https://github.com/SynI20N/IT/blob/systems/lab6/images/3.png">
    Компиляция: <code>gcc -o win.exe sysmets.c -luser32 -lkernel32 -lgdi32</code><br>
    Запуск: <code>.\win.exe</code>
  </p>
<h2>lab7: CLR C++ Winforms Windows 10<br></h2>
  <p>Задача: Создать приложение, которое может управлять реестром, а именно:<br>
   <ul>
     <li>Создавать новые ключи в реестре</li>
     <li>Считывать ключи в реестре</li>
     <li>Удалять ключи из реестра</li>
   </ul> 
   Дополнительно была реализована кнопка Integrity Check, которая сохраняет ветку реестра<br>
   и следить за её изменениями, и при изменении предлагает откатить реестр до исходного состояния<br>
   <p>Приложение в работе:</p>
   <img src="https://github.com/SynI20N/IT/blob/systems/lab7/images/1.png">
   <p>После изменений:</p>
   <img src="https://github.com/SynI20N/IT/blob/systems/lab7/images/2.png">
   <p>Запуск осуществлять исключительно от администратора!</p>
   Запуск: <code>.\lab7\x64\Release\Registry.exe</code>
  </p>
<h2>lab8: CLR C++ Winforms Windows 10<br></h2>
  <p>Задача: Вывести окно для запуска программы с помощью ShellExecute</p>
  <p>Дополнительная задача: Конвертировать с помощью ffmpeg видео, отображая при этом прогресс</p>
  <p>Реализовано: 
    <ul>
      <li>Запуск программы find в проводнике</li>
      <li>Запуск утилиты ffmpeg для конвертации заданного файла в определенный формат</li>
    </ul>
  </p>
  <p>Приложение в работе:</p>
  <img src="https://github.com/SynI20N/IT/blob/systems/lab8/images/1.png">
  <p>Перед запуском (PS): <code>choco install ffmpeg-full</code></p>
  Запуск: <code>.\lab8\x64\Debug\lab8.exe</code>
    
