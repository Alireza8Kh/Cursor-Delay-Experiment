partial class Form1
{
    private System.ComponentModel.IContainer components = null;
    private System.Windows.Forms.Button btnStart;
    private System.Windows.Forms.Label infolabel;
    private System.Windows.Forms.Timer checkTimer;
    private System.Windows.Forms.TextBox headerTextBox;
    protected override void Dispose(bool disposing)
    {
        if (disposing && (components != null))
        {
            components.Dispose();
        }
        base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
        components = new System.ComponentModel.Container();
        btnStart = new Button();
        infolabel = new Label();
        checkTimer = new System.Windows.Forms.Timer(components);
        headerTextBox = new TextBox();
        SuspendLayout();
        // 
        // btnStart
        // 
        btnStart.Enabled = false;
        btnStart.Location = new Point(271, 93);
        btnStart.Name = "btnStart";
        btnStart.Size = new Size(88, 47);
        btnStart.TabIndex = 0;
        btnStart.Text = "Start";
        btnStart.UseVisualStyleBackColor = true;
        btnStart.Click += btnStart_Click;
        // 
        // infolabel
        // 
        infolabel.AutoSize = true;
        infolabel.Location = new Point(12, 35);
        infolabel.Name = "infolabel";
        infolabel.Size = new Size(173, 30);
        //infolabel.Size = new Size(173, 15);
        infolabel.TabIndex = 0;
        infolabel.Text = "Input file header before starting";
        // 
        // checkTimer
        // 
        checkTimer.Interval = 1000;
        checkTimer.Tick += CheckTimer_Tick;
        // 
        // headerTextBox
        // 
        headerTextBox.Location = new Point(12, 107);
        headerTextBox.Name = "headerTextBox";
        headerTextBox.Size = new Size(230, 23);
        headerTextBox.TabIndex = 2;
        headerTextBox.TextChanged += HeaderTextBox_TextChanged;
        // 
        // Form1
        // 
        AutoScaleDimensions = new SizeF(7F, 15F);
        AutoScaleMode = AutoScaleMode.Font;
        //ClientSize = new Size(415, 175);
        ClientSize = new Size(415, 600);
        Controls.Add(btnStart);
        Controls.Add(infolabel);
        Controls.Add(headerTextBox);
        Name = "Form1";
        Text = "Custom Cometa Control App";
        ResumeLayout(false);
        PerformLayout();
    }

    private void HeaderTextBox_TextChanged(object sender, EventArgs e)
    {
        // Enable the start button only if the headerTextBox is not empty
        btnStart.Enabled = !string.IsNullOrWhiteSpace(headerTextBox.Text);
    }
}
