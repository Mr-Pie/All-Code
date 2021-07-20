from PyPDF2 import PdfFileReader, PdfFileWriter
from pathlib import Path
import easygui

def selectpdf():
    fileopenlocation = easygui.fileopenbox(msg='Please select a pdf',
                                           title='Specify File')
    #print(fileopenlocation)
    if(str(fileopenlocation)=='None'):
        #print('Nothing selected')
        return
    if(str.lower(fileopenlocation[-3:])!='pdf'):
        easygui.msgbox("File must be a PDF, dumbass", title="Error")
        fileopenlocation = ''
        selectpdf()
    #print(str(filelocation[-3:])) #checks 3 last characters are 'pdf', else restarts funcs
    input_pdf = PdfFileReader(str(fileopenlocation))
    pdf_writer = PdfFileWriter()
    filesavelocation = filesaveloc()
    #print(str(filesavelocation))
    pageqty = input_pdf.getNumPages()
    #print(pageqty)

#Creating the new PDFs
    for n in range(1, pageqty):
        #print(n)
        page = input_pdf.getPage(n)
        pdf_writer.addPage(page)
        with Path(filesavelocation + '_pg' + str(n) + '.pdf').open(mode="wb") as output_file:
            pdf_writer.write(output_file)
    
def filesaveloc():
    filesavelocation = easygui.filesavebox(msg='Select output location',
                        title='Output PDFs')
    return filesavelocation  

if __name__ == "__main__":
    selectpdf()
