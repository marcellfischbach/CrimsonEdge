
#include <ceImgLoader/jpegloader.hh>
#include <iostream>
#include <ceCore/resource/vfs.hh>
#include <ceCore/graphics/image.hh>
#include <ceCore/resource/filesystemfile.hh>
extern "C" {
#ifdef CE_WIN32
//#include <Windows.h>
#endif

#include <jpeglib.h>
}

namespace ce::img
{


struct my_error_mgr {
  struct jpeg_error_mgr pub;	/* "public" fields */

  jmp_buf setjmp_buffer;	/* for return to caller */
};

JpegLoader::JpegLoader()
{
  CE_CLASS_GEN_CONSTR;


}


bool JpegLoader::CanLoad(const Class* cls, const ResourceLocator& locator) const
{
  return cls->IsAssignableFrom<Image>() &&
    (locator.GetExtension() == "JPEG"
      || locator.GetExtension() == "JPG");
}


iObject* JpegLoader::Load(const Class* cls, const ResourceLocator& locator) const
{
  iFile* ifile = ce::VFS::Get()->Open(locator, eAM_Read, eOM_Binary);
  FILE* infile = ifile->Query<FileSystemFile>()->GetHandle();


  struct jpeg_decompress_struct cinfo;

  struct my_error_mgr jerr;
  cinfo.err = jpeg_std_error(&jerr.pub);

  if (setjmp(jerr.setjmp_buffer)) {
    /* If we get here, the JPEG code has signaled an error.
     * We need to clean up the JPEG object, close the input file, and return.
     */
    jpeg_destroy_decompress(&cinfo);
    return 0;
  }

  /* Now we can initialize the JPEG decompression object. */
  jpeg_create_decompress(&cinfo);

  jpeg_stdio_src(&cinfo, infile);
  
  jpeg_read_header(&cinfo, TRUE);
  jpeg_start_decompress(&cinfo);

  int row_stride = cinfo.output_width * cinfo.output_components;
  JSAMPARRAY buffer = (*cinfo.mem->alloc_sarray)
    ((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);

  uint8_t* image_buffer = new uint8_t[row_stride * cinfo.output_height];
  uint16_t row = 0;
  while (cinfo.output_scanline < cinfo.output_height) {
    /* jpeg_read_scanlines expects an array of pointers to scanlines.
     * Here the array is only one element long, but you could ask for
     * more than one scanline at a time if that's more convenient.
     */
    (void)jpeg_read_scanlines(&cinfo, buffer, 1);
    /* Assume put_scanline_someplace wants a pointer and sample count. */
    //put_scanline_someplace(buffer[0], row_stride);
    memcpy(&image_buffer[(cinfo.output_height - row - 1) * row_stride], buffer[0], row_stride);
    row++;
  }

  ePixelFormat imageFormat = ePF_RGB;
  switch (cinfo.output_components)
  {
  case 1:
    imageFormat = ePF_R;
    break;
  case 2:
    imageFormat = ePF_RG;
    break;
  case 3:
    imageFormat = ePF_RGB;
    break;
  }

  Image* img = new Image(cinfo.output_width, cinfo.output_height, imageFormat);
  img->Copy(0, image_buffer);

  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);

  ifile->Close();


  return img;
}

}