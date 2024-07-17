![[lld-00.jpeg]]

- classname
- attributes
	- name: datatype
	- `+` public
	- `-` private
	- `#` protected
	- underline : static
- methods
	- name: parameters : returntype
	- `+` public
	- `-` private
	- `#` protected
	- underline : static
![[lld-05.png]]
A --|> B   : A _is a_ B (inheritance)


#### Association
**no arrow** : birectional (A can call B, B can call A)
**arrow**: unidirectional (A can call B, B cannot call A)

#### Multiplicity
`1 - 1`
`1..4 - 1`
`* - 1`

#### Role (uses)
mention the role on top of the arrow
"cooks", "eats", "uses"

## HAS-A
#### Aggregation
hollow diamond
B can exist without A
#### Composition
filled diamond
B cannot exist without A

## Inheritance
hollow Arrow

#### Implements
Hollow arrow with dotted line



