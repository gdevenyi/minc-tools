#include  <volume_io.h>

int  main(
    int   argc,
    char  *argv[] )
{
    int        i, n_volumes, n_tag_points, *structure_ids, *patient_ids;
    Real       **tags1, **tags2, *weights;
    char       **labels;
    int        new_n_tag_points, *new_structure_ids, *new_patient_ids;
    Real       **new_tags1, *new_weights;
    char       **new_labels;

    /*--- input the tag file */

    if( input_tag_file( "input_tags.tag", &n_volumes, &n_tag_points,
                        &tags1, &tags2, &weights, &structure_ids,
                        &patient_ids, &labels ) != OK )
        return( 1 );

    /*--- create a new tag point list of only those tag points
          whose x coordinate is nonnegative */

    new_n_tag_points = 0;

    for_less( i, 0, n_tag_points )
    {
        if( tags1[i][0] >= 0.0 )
        {
            /*--- increase the memory allocation of the tag points */

            SET_ARRAY_SIZE( new_tags1, new_n_tag_points,
                            new_n_tag_points+1, 10 );
            ALLOC( new_tags1[new_n_tag_points], 3 );

            SET_ARRAY_SIZE( new_weights, new_n_tag_points,
                            new_n_tag_points+1, 10 );
            SET_ARRAY_SIZE( new_structure_ids, new_n_tag_points,
                            new_n_tag_points+1, 10 );
            SET_ARRAY_SIZE( new_patient_ids, new_n_tag_points,
                            new_n_tag_points+1, 10 );

            SET_ARRAY_SIZE( new_labels, new_n_tag_points,
                            new_n_tag_points+1, 10 );
            ALLOC( new_labels[new_n_tag_points], strlen(labels[i])+1 );

            /*--- copy from the input tags to the new tags */

            new_tags1[new_n_tag_points][0] = tags1[i][0];
            new_tags1[new_n_tag_points][1] = tags1[i][1];
            new_tags1[new_n_tag_points][2] = tags1[i][2];
            new_weights[new_n_tag_points] = weights[i];
            new_structure_ids[new_n_tag_points] = structure_ids[i];
            new_patient_ids[new_n_tag_points] = patient_ids[i];
            (void) strcpy( new_labels[new_n_tag_points], labels[i] );

            /*--- increment the number of new tags */

            ++new_n_tag_points;
        }
    }

    /*--- output the new tags, the subset of the input tags */

    if( output_tag_file( "output.tag", "Removed negative X's",
                         1, new_n_tag_points, new_tags1, NULL,
                         new_weights, new_structure_ids,
                         new_patient_ids, new_labels ) != OK )
        return( 1 );

    free_tag_points( n_volumes, n_tag_points, tags1, tags2,
                     weights, structure_ids, patient_ids, labels );

    free_tag_points( 1, new_n_tag_points, new_tags1, NULL,
                     new_weights, new_structure_ids, new_patient_ids,
                     new_labels );

    return( 0 );
}
