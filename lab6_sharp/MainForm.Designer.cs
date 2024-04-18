/*
 * Created by SharpDevelop.
 * User: david
 * Date: 12.04.2024
 * Time: 11:14
 * 
 * To change this template use Tools | Options | Coding | Edit Standard Headers.
 */
namespace lab8Windows
{
	partial class MainForm
	{
		/// <summary>
		/// Designer variable used to keep track of non-visual components.
		/// </summary>
		private System.ComponentModel.IContainer components = null;
		private System.Windows.Forms.TextBox textBox1;
		private System.Windows.Forms.Label label1;
		private System.Windows.Forms.Button resize;
		private System.Windows.Forms.TextBox textBox2;
		private System.Windows.Forms.TextBox textBox3;
		private System.Windows.Forms.Label label2;
		private System.Windows.Forms.Label label3;
		private System.Windows.Forms.ComboBox comboBox1;
		private System.Windows.Forms.Label label4;
		private System.Windows.Forms.Button formStarButton;
		
		/// <summary>
		/// Disposes resources used by the form.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing)
		{
			if (disposing) {
				if (components != null) {
					components.Dispose();
				}
			}
			base.Dispose(disposing);
		}
		
		/// <summary>
		/// This method is required for Windows Forms designer support.
		/// Do not change the method contents inside the source code editor. The Forms designer might
		/// not be able to load this method if it was changed manually.
		/// </summary>
		private void InitializeComponent()
		{
			this.textBox1 = new System.Windows.Forms.TextBox();
			this.label1 = new System.Windows.Forms.Label();
			this.resize = new System.Windows.Forms.Button();
			this.textBox2 = new System.Windows.Forms.TextBox();
			this.textBox3 = new System.Windows.Forms.TextBox();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.comboBox1 = new System.Windows.Forms.ComboBox();
			this.label4 = new System.Windows.Forms.Label();
			this.formStarButton = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// textBox1
			// 
			this.textBox1.BackColor = System.Drawing.SystemColors.ButtonHighlight;
			this.textBox1.Location = new System.Drawing.Point(321, 55);
			this.textBox1.Multiline = true;
			this.textBox1.Name = "textBox1";
			this.textBox1.ReadOnly = true;
			this.textBox1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
			this.textBox1.Size = new System.Drawing.Size(373, 448);
			this.textBox1.TabIndex = 0;
			this.textBox1.TextChanged += new System.EventHandler(this.TextBox1TextChanged);
			// 
			// label1
			// 
			this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label1.Location = new System.Drawing.Point(399, 23);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(237, 29);
			this.label1.TabIndex = 1;
			this.label1.Text = "Все открытые окна";
			// 
			// resize
			// 
			this.resize.Location = new System.Drawing.Point(70, 74);
			this.resize.Name = "resize";
			this.resize.Size = new System.Drawing.Size(149, 40);
			this.resize.TabIndex = 2;
			this.resize.Text = "Изменить размер";
			this.resize.UseVisualStyleBackColor = true;
			this.resize.Click += new System.EventHandler(this.ResizeClick);
			// 
			// textBox2
			// 
			this.textBox2.Location = new System.Drawing.Point(131, 132);
			this.textBox2.Name = "textBox2";
			this.textBox2.Size = new System.Drawing.Size(100, 22);
			this.textBox2.TabIndex = 3;
			// 
			// textBox3
			// 
			this.textBox3.Location = new System.Drawing.Point(131, 160);
			this.textBox3.Name = "textBox3";
			this.textBox3.Size = new System.Drawing.Size(100, 22);
			this.textBox3.TabIndex = 4;
			// 
			// label2
			// 
			this.label2.Location = new System.Drawing.Point(70, 132);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(29, 23);
			this.label2.TabIndex = 5;
			this.label2.Text = "X";
			// 
			// label3
			// 
			this.label3.Location = new System.Drawing.Point(70, 159);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(37, 23);
			this.label3.TabIndex = 7;
			this.label3.Text = "Y";
			// 
			// comboBox1
			// 
			this.comboBox1.FormattingEnabled = true;
			this.comboBox1.Location = new System.Drawing.Point(808, 74);
			this.comboBox1.Name = "comboBox1";
			this.comboBox1.Size = new System.Drawing.Size(259, 24);
			this.comboBox1.TabIndex = 8;
			// 
			// label4
			// 
			this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
			this.label4.Location = new System.Drawing.Point(857, 39);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(181, 32);
			this.label4.TabIndex = 9;
			this.label4.Text = "Выбрать окно";
			// 
			// formStarButton
			// 
			this.formStarButton.Location = new System.Drawing.Point(829, 204);
			this.formStarButton.Name = "formStarButton";
			this.formStarButton.Size = new System.Drawing.Size(209, 59);
			this.formStarButton.TabIndex = 10;
			this.formStarButton.Text = "Изменить форму \"ЗВЕЗДА\"";
			this.formStarButton.UseVisualStyleBackColor = true;
			this.formStarButton.Click += new System.EventHandler(this.FormStarButtonClick);
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(1218, 541);
			this.Controls.Add(this.formStarButton);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.comboBox1);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.textBox3);
			this.Controls.Add(this.textBox2);
			this.Controls.Add(this.resize);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.textBox1);
			this.Name = "MainForm";
			this.Text = "lab8Windows";
			this.ResumeLayout(false);
			this.PerformLayout();

		}
	}
}
