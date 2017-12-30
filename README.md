-- COPYRIGHT (c) Ioannis Tambouras 2011-2013

You may set the GUC variable euler.style='polar' to set output to polar coordinates, or to 'j' to display in cartisian
coordinates without parenthesis, such as  1,2j .

# constructors

SELECT '1+2j'::euler                         => (1,2)

SELECT '2j'::euler                           => (0,2)

SELECT '1'::euler                            => (1,0)

SELECT '(1,2)'::euler                        => (1,2)

SELECT '1,2j'::euler                         => (1,2)

SELECT '2.236<63.435>'::euler                => (1,2)

SELECT euler_new(1, 2)                       => (1,2)

SELECT euler_new_polar( 2.236,63.435 )       => (1,2)

# Misc

SELECT euler_real( '(3,5)' )                   => 3 

SELECT euler_img(  '(3,5)' )                   => 5 

SELECT euler_dot('3,4j','3,-4j');             => 25

SELECT euler_angle_add('4,4j',20);            => 5.657<65>


# Magnitude, magnitude squared

SELECT |  '(3,4)'::euler                      => 5

SELECT euler_mag('(3,4)'::euler)            => 5

SELECT |^ '(3,4)'::euler                      => 25

SELECT euler_mag_squared('(3,4)')             => 25

# conjugate

SELECT euler_conjugate('(2,4)')             => (2,-4)

SELECT '(2,4)'::euler @                     => (2,-4)

# Arithmetic

SELECT '(2,4)' + '(1,2)'::euler            => (3,6)

SELECT '(2,4)' - '(2,2)'::euler            => (0,2)

SELECT '(2,4)' *  (2,2)'::euler            => (-4,12)

# Conversion from cartesian to polar 

SELECT euler_polar( '(7,-5)' )             => (8.60233,-35.5377)  -- meaning r=8.6 angle=-35

SELECT euler_angle( '(7,-5)' )             => -35.5377

# Conversion from polar to cartesian 

-- r= 8, angle=35

SELECT euler_xy( '(8,35)' )               => (6.55322,4.58861)   


# Relational operators

SELECT '(1,1)' <   '(4,4)'::euler        => true

SELECT '(1,1)' <=  '(4,4)'::euler        => true

SELECT '(4,4)' >=  '(1,1)'::euler        => true

SELECT '(4,4)' >=  '(4,4)'::euler        => true

SELECT '(4,4)' >   '(4,1)'::euler        => true

SELECT '(4,4)' =   '(4,4)'::euler        => true


SELECT euler_abs_cmp( '(4,4)' , '(4,4)' )    => 0

SELECT euler_abs_cmp( '(4,4)' , '(1,1)' )    => 1

SELECT euler_abs_cmp( '(1,1)' , '(4,4)' )    => -1


