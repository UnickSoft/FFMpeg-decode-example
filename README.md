# FFMpeg-decode-example

Example how to use ffmpeg to decode video file. Link to article about [decode with FFMpeg](http://unick-soft.ru/article.php?id=14)

Example shows you the basic FFmpeg functions. Sample program opens video file and stores to a disk first 50 frames. You can change descriptions to setup program:

<pre>
#define FILE_NAME "C:\\temp\\test.avi"
#define OUTPUT_FILE_PREFIX "c:\\temp\\image%d.bmp"
#define FRAME_COUNT 50
</pre>
