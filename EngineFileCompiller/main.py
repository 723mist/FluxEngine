import tkinter as tk
from tkinter import filedialog, messagebox, ttk
import os

class FileCompiler:
    def __init__(self, root):
        self.root = root
        self.root.title("File Compiler")
        self.setup_ui()

    def setup_ui(self):
        # Основная рамка
        frame = ttk.Frame(self.root, padding=10)
        frame.grid(row=0, column=0, sticky=(tk.W, tk.E, tk.N, tk.S))

        # Выбор файла
        ttk.Button(frame, text="Выбрать файл", command=self.select_file).grid(row=0, column=0, pady=5)
        self.file_label = ttk.Label(frame, text="Файл не выбран")
        self.file_label.grid(row=0, column=1, pady=5)

        # Пароль
        ttk.Label(frame, text="Пароль:").grid(row=1, column=0, sticky=tk.W, pady=5)
        self.password_entry = ttk.Entry(frame, show="*")
        self.password_entry.grid(row=1, column=1, pady=5)

        # Кнопки операций
        ttk.Button(frame, text="Скомпилировать", command=self.compile_file).grid(row=2, column=0, pady=5)
        ttk.Button(frame, text="Декомпилировать", command=self.decompile_file).grid(row=2, column=1, pady=5)

    def select_file(self):
        self.selected_file = filedialog.askopenfilename()
        self.file_label.config(text=os.path.basename(self.selected_file))

    def xor_cipher(self, data, key):
        key_bytes = key.encode()
        return bytes([b ^ key_bytes[i % len(key_bytes)] for i, b in enumerate(data)])

    def compile_file(self):
        if not hasattr(self, 'selected_file'):
            messagebox.showerror("Ошибка", "Сначала выберите файл!")
            return

        password = self.password_entry.get()
        if not password:
            messagebox.showerror("Ошибка", "Введите пароль!")
            return

        try:
            with open(self.selected_file, 'rb') as f:
                original_data = f.read()

            encrypted_data = self.xor_cipher(original_data, password)

            output_file = filedialog.asksaveasfilename(
                defaultextension=".bin",
                filetypes=[("Binary files", "*.bin")]
            )
            if output_file:
                with open(output_file, 'wb') as f:
                    f.write(encrypted_data)
                messagebox.showinfo("Успех", "Файл скомпилирован!")
        except Exception as e:
            messagebox.showerror("Ошибка", f"Ошибка обработки: {str(e)}")

    def decompile_file(self):
        if not hasattr(self, 'selected_file'):
            messagebox.showerror("Ошибка", "Сначала выберите файл!")
            return

        password = self.password_entry.get()
        if not password:
            messagebox.showerror("Ошибка", "Введите пароль!")
            return

        try:
            with open(self.selected_file, 'rb') as f:
                encrypted_data = f.read()

            decrypted_data = self.xor_cipher(encrypted_data, password)

            output_file = filedialog.asksaveasfilename(
                defaultextension=".*",
                filetypes=[("All files", "*.*")]
            )
            if output_file:
                with open(output_file, 'wb') as f:
                    f.write(decrypted_data)
                messagebox.showinfo("Успех", "Файл декомпилирован!")
        except Exception as e:
            messagebox.showerror("Ошибка", f"Ошибка обработки: {str(e)}")

if __name__ == "__main__":
    root = tk.Tk()
    app = FileCompiler(root)
    root.mainloop()