/**
 *
 * Module:
 *  helloworldinrust
 *
 * Description:
 *  Hello World in Rust
*/

fn main()
{
    // Right so int, float and all that from C doesn't exist here,
    // just let?
    let a = 10;
    let b = 10;

//  I think it's very rude for a langauge to warn me about MY code style!! 0/10 already
//  I know it's just a warning and all but still, why would you even want that.
//  let aPlusB = a + b;
    let a_plus_b = a + b;


    // So, println! is marco
    // and in rust macros have the ! suffix... looks like they are shouting or exicted...
    // It seems like priting is the only good part about this so far.
    println!( "Hello World: {}", a_plus_b );
}
