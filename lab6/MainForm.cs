using System;
using System.Collections.Generic;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace lab8Windows
{
	public partial class MainForm : Form
	{
		// Добавляем хук для отслеживания изменений активного окна
		private delegate void WinEventDelegate(IntPtr hWinEventHook, uint eventType, IntPtr hwnd, int idObject, int idChild, uint dwEventThread, uint dwmsEventTime);
		private const uint EVENT_SYSTEM_FOREGROUND = 0x0003;
		private const uint WINEVENT_OUTOFCONTEXT = 0;
		private static WinEventDelegate procDelegate = new WinEventDelegate(WinEventProc);
		private static IntPtr hhook = IntPtr.Zero;

		public MainForm()
		{
			InitializeComponent();
			EnumerateWindows();

			// Устанавливаем хук
			SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, IntPtr.Zero, procDelegate, 0, 0, WINEVENT_OUTOFCONTEXT);
		}

		public void EnumerateWindows()
		{
			// Очищаем текстовое поле перед обновлением
			textBox1.Clear();

			EnumWindows((hWnd, lParam) => {
				int length = GetWindowTextLength(hWnd);
				if (length > 0) {
					StringBuilder sb = new StringBuilder(length + 1);
					GetWindowText(hWnd, sb, sb.Capacity);
					string windowTitle = sb.ToString();
					textBox1.AppendText(windowTitle + Environment.NewLine);
				}
				return true;
			}, IntPtr.Zero);
		}

		// Метод обработки события изменения активного окна
		private static void WinEventProc(IntPtr hWinEventHook, uint eventType, IntPtr hwnd, int idObject, int idChild, uint dwEventThread, uint dwmsEventTime)
		{
			// Получаем главную форму
			MainForm mainForm = null;
			foreach (Form form in Application.OpenForms) {
				if (form is MainForm) {
					mainForm = (MainForm)form;
					break;
				}
			}
			if (mainForm != null) {
				// Вызываем метод обновления списка окон
				mainForm.EnumerateWindows();
			}
		}

		[DllImport("user32.dll")]
		private static extern IntPtr GetForegroundWindow();

		[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		private static extern int GetWindowTextLength(IntPtr hWnd);

		[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
		private static extern int GetWindowText(IntPtr hWnd, StringBuilder lpString, int nMaxCount);

		[DllImport("user32.dll")]
		[return: MarshalAs(UnmanagedType.Bool)]
		private static extern bool EnumWindows(EnumWindowsProc lpEnumFunc, IntPtr lParam);

		private delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);

		[DllImport("user32.dll", EntryPoint = "GetClassLongPtr")]
		private static extern IntPtr GetClassLongPtr(IntPtr hWnd, int nIndex);

		[DllImport("shell32.dll", CharSet = CharSet.Auto)]
		private static extern uint ExtractIconEx(string lpszFile, int nIconIndex, out IntPtr phiconLarge, IntPtr phiconSmall, uint nIcons);

		// Добавляем хук WinEvent
		[DllImport("user32.dll")]
		private static extern IntPtr SetWinEventHook(uint eventMin, uint eventMax, IntPtr hmodWinEventProc, WinEventDelegate lpfnWinEventProc, uint idProcess, uint idThread, uint dwFlags);

		[DllImport("user32.dll")]
		private static extern bool UnhookWinEvent(IntPtr hWinEventHook);
        
		// Освобождаем хук при закрытии формы
		protected override void OnFormClosed(FormClosedEventArgs e)
		{
			base.OnFormClosed(e);
			UnhookWinEvent(hhook);
		}
        
		void TextBox1TextChanged(object sender, EventArgs e)
		{
		}
		void ResizeClick(object sender, EventArgs e)
		{
			// Получаем дескриптор текущего окна
			IntPtr handle = this.Handle;

			// Увеличиваем размеры окна на 100 пикселей по ширине и высоте
			SetWindowPos(handle, IntPtr.Zero, 0, 0, Int32.Parse(this.textBox2.Text) + 100, Int32.Parse(this.textBox3.Text) + 100, SWP_NOMOVE | SWP_NOZORDER);
		}

		[DllImport("user32.dll")]
		private static extern bool SetWindowPos(IntPtr hWnd, IntPtr hWndInsertAfter, int X, int Y, int cx, int cy, uint uFlags);

		private const uint SWP_NOMOVE = 0x0002;
		private const uint SWP_NOZORDER = 0x0004;
	}
}
