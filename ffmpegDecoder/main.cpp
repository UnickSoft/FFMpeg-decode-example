// ffmpegDecoder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ffmpegDecode.h"
#include <windows.h>

#define FILE_NAME          "C:\\temp\\test.avi"
#define OUTPUT_FILE_PREFIX "c:\\temp\\image%d.bmp"
#define FRAME_COUNT        50

bool BMPSave(const char *pFileName, AVFrame * frame, int w, int h)
{
	bool bResult = false;

	if (frame)
	{
		FILE* file = fopen(pFileName, "wb");

		if (file)
		{
			// RGB image
			int imageSizeInBytes = 3 * w * h;
			int headersSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
			int fileSize = headersSize + imageSizeInBytes;

			uint8_t * pData = new uint8_t[headersSize];

			if (pData != NULL)
			{
				BITMAPFILEHEADER& bfHeader = *((BITMAPFILEHEADER *)(pData));

				bfHeader.bfType = 'MB';
				bfHeader.bfSize = fileSize;
				bfHeader.bfOffBits = headersSize;
				bfHeader.bfReserved1 = bfHeader.bfReserved2 = 0;

				BITMAPINFOHEADER& bmiHeader = *((BITMAPINFOHEADER *)(pData + headersSize - sizeof(BITMAPINFOHEADER)));

				bmiHeader.biBitCount = 3 * 8;
				bmiHeader.biWidth    = w;
				bmiHeader.biHeight   = h;
				bmiHeader.biPlanes   = 1;
				bmiHeader.biSize     = sizeof(bmiHeader);
				bmiHeader.biCompression = BI_RGB;
				bmiHeader.biClrImportant = bmiHeader.biClrUsed = 
					bmiHeader.biSizeImage = bmiHeader.biXPelsPerMeter = 
					bmiHeader.biYPelsPerMeter = 0;

				fwrite(pData, headersSize, 1, file);

				uint8_t *pBits = frame->data[0] + frame->linesize[0] * h - frame->linesize[0];
				int nSpan      = -frame->linesize[0];

				int numberOfBytesToWrite = 3 * w;

				for (size_t i = 0; i < h; ++i, pBits += nSpan)	
				{
					fwrite(pBits, numberOfBytesToWrite, 1, file);
				}

				bResult = true;
				delete [] pData;				
			}

			fclose(file);
		}
	}

	return bResult;
}


int _tmain(int argc, _TCHAR* argv[])
{
  FFmpegDecoder decoder;

  if (decoder.OpenFile(std::string(FILE_NAME)))
  {
    int w = decoder.GetWidth();
    int h = decoder.GetHeight();

    for (int i = 0; i < FRAME_COUNT; i++)
    {
      AVFrame * frame = decoder.GetNextFrame();
      if (frame)
      {
        char filename[MAX_PATH];
        sprintf(filename, OUTPUT_FILE_PREFIX, i);
		if (!BMPSave(filename, frame, frame->width, frame->height))
        {
          printf("Cannot save file %s\n", filename);
        }
        av_free(frame->data[0]);
        av_free(frame);
      }
    }

    decoder.CloseFile();
  }
  else
  {
    printf ("Cannot open file " FILE_NAME "\n");
  }

	return 0;
}

