import os
import tkinter as tk
from tkinter import filedialog
import shutil
import time

folder_names = {
    "Images": ["jpg", "jpeg", "png", "gif", "tiff", "bmp", "svg"],
    "Videos": ["mp4", "avi", "mov", "wmv", "mkv", "flv", "webm", "vob", "ogv", "ogg", "drc", "mng", "avi", "asf", "wmv", "rm", "rmvb", "mpg", "mpeg", "mpe", "mp4", "m4p", "m4v", "svi", "3gp", "3g2", "mxf", "roq", "nsv", "flv", "f4v", "f4p", "f4a", "f4b"],
    "Documents": ["txt", "pdf", "doc", "docx", "odt", "rtf", "tex", "wks", "wps", "wpd", "xls", "xlt", "xlw", "mdb", "fodt", "ods", "odp", "odg", "odf", "odb", "odc", "odm", "ott", "ots", "odp", "otp", "odg"],
    "Archives": ["zip", "rar", "7z", "tar", "gz", "bz2", "xz", "iso", "dmg", "pkg"],
    "Music": ["mp3", "m4a", "m4b", "aif", "aiff", "aifc", "ogg", "oga", "wav", "wma", "flac", "alac", "ape", "mpc", "tta", "ac3", "dts", "mka", "m3u", "wpl", "pls", "m3u", "m3u8"],
    "Executables": ["exe", "msi"],
    "Fonts": ["ttf", "otf", "ttc", "otc", "pfa", "pfb", "pfr", "pfm", "afm", "fnt", "fon", "otf", "sfd", "woff", "woff2", "eot", "font", "fnt", "fon"],
    "Code": ["py", "c", "cpp", "h", "hpp", "cs", "java", "js", "html", "htm", "xhtml", "css", "xml", "xsl", "xslt", "php", "jsp", "asp", "aspx", "sh", "bat", "cmd", "pl", "rb", "py", "lua", "coffee", "ts", "ts", "ts", "ts"],
    "Operating Systems": ["iso", "img"]
}

def get_dir():
    root = tk.Tk()
    root.withdraw()  # Hide the main window
    folder_path = filedialog.askdirectory()
    print("Selected folder:", folder_path)
    return folder_path

def get_extension_folder(extension):
    for folder, extensions in folder_names.items():
        if extension.lower() in extensions:
            return folder
    return "Other"

def organize_to_folders(folder_path):
    for entry in os.listdir(folder_path):
        entry_path = os.path.join(folder_path, entry)
        if os.path.isfile(entry_path):
            _, extension = os.path.splitext(entry)
            if extension:
                folder_name = get_extension_folder(extension[1:])
                folder_path_for_extension = os.path.join(folder_path, folder_name)
                os.makedirs(folder_path_for_extension, exist_ok=True)
                shutil.move(entry_path, os.path.join(folder_path_for_extension, entry))

if __name__ == "__main__":
    folder_path = get_dir()
    start_time = time.time()
    organize_to_folders(folder_path)
    print("Organizing completed.")
    elapsed_time = time.time() - start_time
    print("Execution time: {:.2f} seconds".format(elapsed_time))
