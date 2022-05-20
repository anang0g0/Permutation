// y: シード値（32ビット整数）
extern crate rand;
use rand::Rng;



/*
    Fisher-Yates shuffle による方法
    配列の要素をランダムシャッフルする
*/
fn random_shuffule(array:[i32;8192], size:i32)->&[i32;8192]
{
    let mut i:usize;
    let a:usize;
    let mut b:usize;

    for i in (1..size).rev()
    {
        a = (i - 1) as usize;
        b = rand::thread_rng().gen_range(1, i) as usize;
        // ソートするキーの型
        //(array[a] , array[b] ) = ( array[b], array[a] )
    }
    &array
}

fn main() {
    let mut a:[i32;8192];
    let mut i:i32;

    for i in 1..8192
    {
    a[i]= rand::thread_rng().gen_range(1, 8192) as i32;
    }

    //random_shuffule(a,8192);
    
    for i in 1..8192{
        print!("{},",a[i]);
    }
    println!("\n");
    println!("Hello, world!");
}
