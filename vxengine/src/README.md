# AMD VXEngine
VXEngine is a library to create and run OpenVX graphs, with a simple, easy-to-use interface. It encapsulates most of the routine OpenVX calls, thus speeding up development and enabling rapid prototyping. As input, VXEngine takes a graph described in GDF (Graph Description Format), a simple and intuitive syntax to describe the various data, nodes, and their dependencies. The library has other useful features, such as, file read/write, data compares, image and keypoint data visualization, etc.

If available, this project uses OpenCV for camera capture and image display.

##  GDF Syntax
         
    The supported list of OpenVX built-in kernel names is given below:
        org.khronos.openvx.color_convert
        org.khronos.openvx.channel_extract
        org.khronos.openvx.channel_combine
        org.khronos.openvx.sobel_3x3
        org.khronos.openvx.magnitude
        org.khronos.openvx.phase
        org.khronos.openvx.scale_image
        org.khronos.openvx.table_lookup
        org.khronos.openvx.histogram
        org.khronos.openvx.equalize_histogram
        org.khronos.openvx.absdiff
        org.khronos.openvx.mean_stddev
        org.khronos.openvx.threshold
        org.khronos.openvx.integral_image
        org.khronos.openvx.dilate_3x3
        org.khronos.openvx.erode_3x3
        org.khronos.openvx.median_3x3
        org.khronos.openvx.box_3x3
        org.khronos.openvx.gaussian_3x3
        org.khronos.openvx.custom_convolution
        org.khronos.openvx.gaussian_pyramid
        org.khronos.openvx.accumulate
        org.khronos.openvx.accumulate_weighted
        org.khronos.openvx.accumulate_square
        org.khronos.openvx.minmaxloc
        org.khronos.openvx.convertdepth
        org.khronos.openvx.canny_edge_detector
        org.khronos.openvx.and
        org.khronos.openvx.or
        org.khronos.openvx.xor
        org.khronos.openvx.not
        org.khronos.openvx.multiply
        org.khronos.openvx.add
        org.khronos.openvx.subtract
        org.khronos.openvx.warp_affine
        org.khronos.openvx.warp_perspective
        org.khronos.openvx.harris_corners
        org.khronos.openvx.fast_corners
        org.khronos.openvx.optical_flow_pyr_lk
        org.khronos.openvx.remap
        org.khronos.openvx.halfscale_gaussian
    
    The available GDF commands are:
      import <libraryName>
          Import kernels in a library using vxLoadKernel API.

      type <typeName> userstruct:<size-in-bytes>
          Create an OpenVX user defined structure using vxRegisterUserStruct API.
          The <typeName> can be used as a type in array object.

      data <dataName> = <data-description>
          Create an OpenVX data object in context using the below syntax for
          <data-description>:
              array:<data-type>,<capacity>
              convolution:<columns>,<rows>
              distribution:<numBins>,<offset>,<range>
              delay:<exemplar>,<slots>
              image:<width>,<height>,<image-format>[,<range>][,<space>]
              uniform-image:<width>,<height>,<image-format>,<uniform-pixel-value>
              image-from-roi:<master-image>,rect{<start-x>;<start-y>;<end-x>;<end-y>}
              image-from-handle:<image-format>,{<dim-x>;<dim-y>;<stride-x>;<stride-y>}[+...],<memory-type>
              image-from-channel:<master-image>,<channel>
              lut:<data-type>,<count>
              matrix:<data-type>,<columns>,<rows>
              pyramid:<numLevels>,half|orb|<scale-factor>,<width>,<height>,<image-format>
              remap:<srcWidth>,<srcHeight>,<dstWidth>,<dstHeight>
              scalar:<data-type>,<value>
              threshold:<thresh-type>,<data-type>
              tensor:<num-of-dims>,{<dim0>,<dim1>,...},<data-type>,<fixed-point-pos>
              tensor-from-roi:<master-tensor>,<num-of-dims>,{<start0>,<start1>,...},{<end0>,<end1>,...}
              tensor-from-handle:<num-of-dims>,{<dim0>,<dim1>,...},<data-type>,<fixed-point-pos>,{<stride0>,<stride1>,...},<num-alloc-handles>,<memory-type>
          For virtual object in default graph use the below syntax for
          <data-description>:
              virtual-array:<data-type>,<capacity>
              virtual-image:<width>,<height>,<image-format>
              virtual-pyramid:<numLevels>,half|orb|<scale-factor>,<width>,<height>,<image-format>
              virtual-tensor:<num-of-dims>,{<dim0>,<dim1>,...},<data-type>,<fixed-point-pos>

          where:
              <master-image> can be name of a image data object (including $1, $2, ...)
              <master-tensor> can be name of a tensor data object (including $1, $2, ...)
              <exemplar> can be name of a data object (including $1, $2, ...)
              <thresh-type> can be BINARY,RANGE
              <uniform-pixel-value> can be an integer or {<byte>;<byte>;...}
              <image-format> can be RGB2,RGBX,IYUV,NV12,U008,S016,U001,F032,...
              <data-type> can be UINT8,INT16,INT32,UINT32,FLOAT32,ENUM,BOOL,SIZE,
                                 KEYPOINT,COORDINATES2D,RECTANGLE,<typeName>,...
              <range> can be vx_channel_range_e enums FULL or RESTRICTED
              <space> can be vx_color_space_e enums BT709 or BT601_525 or BT601_625

      node <kernelName> [<argument(s)>]
          Create a node of specified kernel in the default graph with specified
          node arguments. Node arguments have to be OpenVX data objects created
          earlier in GDF or data objects specified on command-line accessible as
          $1, $2, etc. For scalar enumerations as node arguments, use !<enumName>
          syntax (e.g., !VX_CHANNEL_Y for channel_extract node).

      include <file.gdf>
          Specify inclusion of another GDF file.

      shell
          Start a shell command session.

      set <option> [<value>]
          Specify or query the following global options:
              set verbose [on|off]
                  Turn on/off verbose option.
              set frames [[<start-frame>:]<end-frame>|eof|live|default]
                  Specify input frames to be processed. Here are some examples:
                      set frames 10      # process frames 0 through 9
                      set frames 1:10    # process frames 1 through 9
                      set frames eof     # process all frames till end-of-file
                      set frames live    # input is live until terminated by user
                      set frames default # process all frames specified on input
              set dump-profile [on|off]
                  Turn on/off profiler output.
              set wait [key|<milliseconds>]
                  Specify wait time between frame processing to give extra time
                  for viewing. Or wait for key press between frames.
              set compare [on|off|discard-errors]
                  Turn on/off data compares or just discard data compare errors.
              set use-schedule-graph [on|off]
                  Turn on/off use of vxScheduleGraph instead of vxProcessGraph.
              set dump-data-config [<dumpFilePrefix>,<obj-type>[,<obj-type>[...]]]
                  Specify dump data config for portion of the graph. To disable
                  don't specify any config.

      graph <command> [<arguments> ...]
          Specify below graph specific commands:
              graph auto-age [<delayName> [<delayName> ...]]
                  Make the default graph use vxAgeDelay API for the specified
                  delay objects after processing each frame.
              graph affinity [CPU|GPU[<device-index>]]
                  Specify graph affinity to CPU or GPU.
              graph save-and-reset <graphName>
                  Verify the default graph and save it as <graphName>. Then
                  create a new graph as the default graph. Note that the earlier
                  virtual data object won't be available after graph reset.
              graph reset [<graphName(s)>]
                  Reset the default or specified graph(s). Note that the earlier
                  virtual data object won't be available after graph reset.
              graph launch [<graphName(s)>]
                  Launch the default or specified graph(s).
              graph info [<graphName(s)>]
                  Show graph details for debug.

      rename <dataNameOld> <dataNameNew>
          Rename a data object\n"

      init <dataName> <initial-value>
          Initialize data object with specified value.
          - convolution object initial values can be:
              {<value1>;<value2>;...<valueN>}
              scale{<scale>}
          - matrix object initial values can be:
              {<value1>;<value2>;...<valueN>}
          - remap object initial values can be:
              dst is same as src: same
              dst is 90 degree rotation of src: rotate-90
              dst is 180 degree rotation of src: rotate-180
              dst is 270 degree rotation of src: rotate-270
              dst is horizontal flip of src: hflip
              dst is vertical flip of src: vflip
          - threshold object initial values can be:
              For VX_THRESHOLD_TYPE_BINARY: <value>
              For VX_THRESHOLD_TYPE_RANGE: {<lower>;<upper>}
          - image object initial values can be:
              Binary file with image data. For images created from handle,
              the vxSwapHandles API will be invoked before executing the graph.
          - tensor object initial values can be:
              Binary file with tensor data.
              To replicate a file multiple times, use @repeat~N~<fileName>.
              To fill the tensor with a value, use @fill~f32~<float-value>,
              @fill~i32~<int-value>, @fill~i16~<int-value>, or @fill~u8~<uint-value>.

      read <dataName> <fileName> [ascii|binary] [<option(s)>]
          Read frame-level data from the specified <fileName>.
          - images can be read from containers (such as, .jpg, .avi, .mp4, etc.)
            as well as raw binary files
          - certain raw data formats support reading data for all frames from a
            single file (such as, video.yuv, video.rgb, video.avi etc.)
            The data objects that support this feature are image, scalar, and
            threshold data objects.
          - certain data formats support printf format-syntax (e.g., joy_%04d.yuv)
            to read individual data from separate files. Note that scalar and
            threshold data objects doesn't support this feature. Also note that
            pyramid objects expect all frames of each level in separate files.
          - convolution objects support the option: scale
            This will read scale value as the first 32-bit integer in file(s).

      write <dataName> <fileName> [ascii|binary] [<option(s)>]
          Write frame-level data to the specified <fileName>.
          - certain raw data formats support writing data for all frames into a
            single file (such as, video.yuv, video.rgb, video.u8, etc.)
            The data objects that support this feature are image, scalar, and
            threshold data objects.
          - certain data formats support printf format-syntax (e.g., joy_%04d.yuv)
            to write individual data from separate files. Note that scalar and
            threshold data objects doesn't support this feature. Also note that
            pyramid objects expect all frames of each level in separate files.
          - convolution objects support the option: scale
            This will write scale value as the first 32-bit integer in file(s).

      compare <dataName> <fileName> [ascii|binary] [<option(s)>]
          Compare frame-level data from the specified <fileName>.
          - certain raw data formats support comparing data for all frames from a
            single file (such as, video.yuv, video.rgb, video.u8, etc.)
            The data objects that support this feature are image, scalar, and
            threshold data objects.
          - certain data formats support printf format-syntax (e.g., joy_%04d.yuv)
            to read individual data from separate files. Note that scalar and
            threshold data objects doesn't support this feature.
          - array objects with VX_TYPE_KEYPOINT data type support the options:
              specify tolerance: err{<x>;<y>;<strength>[;<%mismatch>]}
              specify compare log file: log{<fileName>}
          - array objects with VX_TYPE_COORDINATES2D data type support the options:
              specify tolerance: err{<x>;<y>[;<%mismatch>]}
              specify compare log file: log{<fileName>}
          - convolution objects support the option:
              read scale value as the first 32-bit integer in file(s): scale
          - image and pyramid objects support the options:
              specify compare region: rect{<start-x>;<start-y>;<end-x>;<end-y>}
              specify valid pixel difference: err{<min>;<max>}
              specify pixel checksum to compare: checksum
              specify generate checksum: checksum-save-instead-of-test
          - matrix objects support the options:
              specify tolerance: err{<tolerance>}
          - remap objects support the options:
              specify tolerance: err{<x>;<y>}
          - scalar objects support the option:
              specify that file specifies inclusive range of valid values: range

      view <dataName> <windowName>
          Display frame-level data in a window with title <windowName>. Each window
          can display an image data object and optionally additional other data
          objects overlaid on top of the image.
          - supported data object types are: array, distribution, image, lut,
            scalar, and delay.
          - display of array, distribution, lut, and scalar objects are
            overlaid on top of an image with the same <windowName>.
          - delay object displays reference in the slot#0 of current time.

      directive <dataName> <directive>
          Specify a directive to data object. Only a few directives are supported:
          - Use sync-cl-write directive to issue VX_DIRECTIVE_AMD_COPY_TO_OPENCL
            directive whenever data object is updated using init or read commands.
            Supported for array, image, lut, and remap data objects only.
          - Use readonly directive to issue VX_DIRECTIVE_AMD_READ_ONLY directive
            that informs the OpenVX framework that object won't be updated after
            init command. Supported for convolution and matrix data objects only.

      pause
          Wait until a key is pressed before processing next GDF command.

      help [command]
          Show the GDF command help.

      exit
          Exit from shell or included GDF file.

      quit
          Abort the application.

 
