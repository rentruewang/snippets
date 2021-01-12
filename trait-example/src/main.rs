trait Animal: AnimalClone {
    fn speak(&self);
}

// Splitting AnimalClone into its own trait allows us to provide a blanket
// implementation for all compatible types, without having to implement the
// rest of Animal.  In this case, we implement it for all types that have
// 'static lifetime (*i.e.* they don't contain non-'static pointers), and
// implement both Animal and Clone.  Don't ask me how the compiler resolves
// implementing AnimalClone for Animal when Animal requires AnimalClone; I
// have *no* idea why this works.
trait AnimalClone {
    fn clone_box(&self) -> Box<dyn Animal>;
}

impl<T> AnimalClone for T
where
    T: 'static + Animal + Clone,
{
    fn clone_box(&self) -> Box<dyn Animal> {
        Box::new(self.clone())
    }
}

// We can now implement Clone manually by forwarding to clone_box.
impl Clone for Box<dyn Animal> {
    fn clone(&self) -> Box<dyn Animal> {
        self.clone_box()
    }
}

#[derive(Clone)]
struct Dog {
    name: String,
}

impl Dog {
    fn new(name: &str) -> Dog {
        Dog {
            name: name.to_string(),
        }
    }
}

impl Animal for Dog {
    fn speak(&self) {
        println!("{}: ruff, ruff!", self.name);
    }
}

#[derive(Clone)]
struct AnimalHouse {
    animal: Box<dyn Animal>,
}

fn main() {
    let house = AnimalHouse {
        animal: Box::new(Dog::new("Bobby")),
    };
    let house2 = house.clone();
    house2.animal.speak();
}
