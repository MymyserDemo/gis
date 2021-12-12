namespace AutoPrint
{
    partial class MainView
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.dataGridView = new System.Windows.Forms.DataGridView();
            this.textBoxLocate = new System.Windows.Forms.TextBox();
            this.buttonReference = new System.Windows.Forms.Button();
            this.webBrowser = new System.Windows.Forms.WebBrowser();
            this.textBoxStart = new System.Windows.Forms.TextBox();
            this.textBoxEnd = new System.Windows.Forms.TextBox();
            this.buttonExecute = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView
            // 
            this.dataGridView.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView.Location = new System.Drawing.Point(9, 41);
            this.dataGridView.Name = "dataGridView";
            this.dataGridView.RowTemplate.Height = 21;
            this.dataGridView.Size = new System.Drawing.Size(240, 531);
            this.dataGridView.TabIndex = 0;
            // 
            // textBoxLocate
            // 
            this.textBoxLocate.Location = new System.Drawing.Point(258, 10);
            this.textBoxLocate.Name = "textBoxLocate";
            this.textBoxLocate.Size = new System.Drawing.Size(588, 19);
            this.textBoxLocate.TabIndex = 1;
            // 
            // buttonReference
            // 
            this.buttonReference.Location = new System.Drawing.Point(852, 8);
            this.buttonReference.Name = "buttonReference";
            this.buttonReference.Size = new System.Drawing.Size(75, 23);
            this.buttonReference.TabIndex = 2;
            this.buttonReference.Text = "参照";
            this.buttonReference.UseVisualStyleBackColor = true;
            this.buttonReference.Click += new System.EventHandler(this.buttonReference_Click);
            // 
            // webBrowser
            // 
            this.webBrowser.Location = new System.Drawing.Point(258, 41);
            this.webBrowser.MinimumSize = new System.Drawing.Size(20, 20);
            this.webBrowser.Name = "webBrowser";
            this.webBrowser.Size = new System.Drawing.Size(669, 531);
            this.webBrowser.TabIndex = 3;
            this.webBrowser.Url = new System.Uri("https://en.wikipedia.org/w/index.php?title=Leonhard_Euler&printable=yes", System.UriKind.Absolute);
            // 
            // textBoxStart
            // 
            this.textBoxStart.Location = new System.Drawing.Point(9, 10);
            this.textBoxStart.Name = "textBoxStart";
            this.textBoxStart.Size = new System.Drawing.Size(70, 19);
            this.textBoxStart.TabIndex = 4;
            // 
            // textBoxEnd
            // 
            this.textBoxEnd.Location = new System.Drawing.Point(104, 10);
            this.textBoxEnd.Name = "textBoxEnd";
            this.textBoxEnd.Size = new System.Drawing.Size(70, 19);
            this.textBoxEnd.TabIndex = 5;
            // 
            // buttonExecute
            // 
            this.buttonExecute.Location = new System.Drawing.Point(180, 8);
            this.buttonExecute.Name = "buttonExecute";
            this.buttonExecute.Size = new System.Drawing.Size(70, 23);
            this.buttonExecute.TabIndex = 6;
            this.buttonExecute.Text = "実行";
            this.buttonExecute.UseVisualStyleBackColor = true;
            this.buttonExecute.Click += new System.EventHandler(this.buttonExecute_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(83, 13);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(17, 12);
            this.label1.TabIndex = 7;
            this.label1.Text = "～";
            // 
            // MainView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(939, 584);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.buttonExecute);
            this.Controls.Add(this.textBoxEnd);
            this.Controls.Add(this.textBoxStart);
            this.Controls.Add(this.webBrowser);
            this.Controls.Add(this.buttonReference);
            this.Controls.Add(this.textBoxLocate);
            this.Controls.Add(this.dataGridView);
            this.Name = "MainView";
            this.Text = "自動印刷";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView;
        private System.Windows.Forms.TextBox textBoxLocate;
        private System.Windows.Forms.Button buttonReference;
        private System.Windows.Forms.WebBrowser webBrowser;
        private System.Windows.Forms.TextBox textBoxStart;
        private System.Windows.Forms.TextBox textBoxEnd;
        private System.Windows.Forms.Button buttonExecute;
        private System.Windows.Forms.Label label1;
    }
}

