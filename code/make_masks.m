
% creates the mask file for the bow_slic training and testing
% it goes through all the jpg files in one directory, let's you outline a
% polygon, and writes out a png file with the mask. 
%
% to run:
% >> make_masks
% then follow instuctions

close all
clear

% you can make the same mask for "step" images. These images will be summed
% up and you can draw one mask for it. This is practical if the images are
% similar (e.g. masking the road from a highway).
step = 1;
% directory that contains the jpg images for which the masks are made
main_dir = 'vsfm/bin/Accident/';
im_files = dir([main_dir,'/*.jpg']);

[ni1,ni2] = size(im_files);


for k=1:step:ni1
%for k=1:step:10
    
% summing up "step" images into one image:
    for i=k:min(k+step-1,ni1)
        nnorm = min(k+step-1,ni1)-k+1;
        im = imread([main_dir,'/',im_files(i).name]);
        if(~exist('im_sum','var'))
            im_sum = im/nnorm;
        else
            im_sum = im_sum + im/nnorm;
        end
        
    end
    
    % draw the polygon:
    figure(1)
    image(im_sum)
    
    [height, width, icol] = size(im);
    fprintf(1,'click on points to define polygon of mask, right click to stop');
    mask0 = zeros(height, width);
    for count = 1:5  % 5 chance to draw polygons. right click to quit one chance
        [x, y] = getpts;    
        mask0 = mask0 + poly2mask(x, y, height, width);
    end
    
    mask = uint8(ones([height,width]));
    
    mask(mask0==0) = 255;
    % draw the resulting mask:
    figure(2)
    imshow(mask)
    
    % write a mask file for each image:
    for i=k:min(k+step-1,ni1)
        imwrite(mask,[main_dir,'/',im_files(i).name(1:end-4),'_mask.png']);
    end
    
    im_sum = im_sum*0;
    
end
