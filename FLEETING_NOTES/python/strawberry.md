
# GraphQL
- Query lang for APIs
- runtime for exec'ing those queries against your data
- clients request EXACTLY the data they need! ::: Efficient data fetching
    - with REST::: underfetching/overfetching happen :(
- SINGLE ENDPOINT!!!
- Strongly typed schema ::: API is defined by a schema ::: Self documenting

Example
`query.gql`
```graphql
query getRockets{
    rocket{
        name
        thrust
        captain{
            name
            callsign
        }
    }
}
```
`response.json`
```json
{
    "name": "Saturn V",
    "thrust": 7891000,
    "captain":{
        "name": "Neil Armstrong",
        "callsign": "Neil"
    }
}
```

Another Example
`query.gql`
```graphql
query HomePage{
    conference(id: "pycon-11") {
        title
        description
        events{
            title
        }
        faqs{
            question
            answer
        }
    }
}
```
`response.json`
```json
{
    "conference":{
        "title": "PyCon Italia 11",
        "description": "Eget doner...",
        "events":[{
            "title": "Python Pizza",
        }],
        "faqs": [{
            "question": "When?",
            "answer": "2-5 April 2020"
        }]
    }
}
```
...Underlying Types
`types.gql`
```graphql
type Query {
    conference(code: ID!): Conference
}
type Conference{
    title: String!
    description: String!
    faqs: [FAQ!]!
    events: [Event!]!
}
type Event{
    title: String!
    image: String!
}
```
#### Queries : to fetch
```graphql
query HomePage{
    conference(id: "pycon-11") {
        title
        description
        events{
            title
        }
        faqs{
            question
            answer
        }
    }
}
```

#### Mutations : to create/update/delete
```graphql
mutation {
  addBook(title: "New Book", authorId: 1) {
    id
    title
  }
}
```

#### How does GraphQL work?
1. `http POST /graphql`
2. The "document" is **parsed** ::: AST -> validation
3. Query is executed ::: call the **resolvers** attached to the fields




#### Resolvers
A resolver is a function that fetches data for a specific field.
Resolvers connect queries and mutations to backend logic. They define how data is fetched or manipulated.
eg:
```py
def resolve_conference(code):
    return {
        "title": "ABC"
    }
```

#### Schemas : GraphQL [types|queries|mutations]
```graphql
type Conference{
    title: String!
    description: String!
    faqs: [FAQ!]!
    events: [Event!]!
}
```

---

# Strawberry
```python
pip install strawberry-graphql
```
- Python library for building GraphQL APIs. (works well with Django too)
- Uses Python type annotations (type safety) ::: inspired by `dataclasses`
- Works well with Django models (ORM integration)
- Extensibility
    - middleware
    - custom resolvers
    - subscriptions


### Defining Types
```graphql
type Conference{
    title: String!
    description: String!
    faqs: [FAQ!]!
    events: [Event!]!
}
```
...becomes

```python
import strawberry
from typing import List

@strawberry.type
class Conference:
    title: str = strawberry.field(resolver=get_field)


    description: str
    faqs: List[FAQ]
    events: List[Event]
```

### Queries
```python
@strawberry.type
class Query:
    @strawberry.field
    def books(self) -> list[Book]:
        return [Book(title="Django for Beginners", author="William Vincent")]
```

### Creating Mutations
Mutations modify data. Example:
```python
@strawberry.type
class Mutation:
    @strawberry.mutation
    def add_book(self, title: str, author: str) -> Book:
        return Book(title=title, author=author)
```

### Integrating with Django
Include Strawberry in your Django project:
```py
//SETTINGS.py

INSTALLED_APPS = [
    ...
    'strawberry.contrib.django'
]
```

views...
```python

from strawberry.django.views import GraphQLView
from your_project.schema import schema

urlpatterns = [
    path("graphql/", GraphQLView.as_view(schema=schema)),
]
```

## 4. Advanced Topics

### Custom Resolvers
Custom resolvers allow more complex data fetching:
```python
@strawberry.type
class Query:
    @strawberry.field
    def book_by_title(self, title: str) -> Book:
        # Fetch book from database
        return Book(title=title, author="Unknown")
```

### Middleware
Middleware adds custom logic to GraphQL requests. Example:
```python
from strawberry.types import Info

def my_middleware(next_, root, info: Info, *args, **kwargs):
    print("Request received")
    return next_(root, info, *args, **kwargs)
```

### Authentication and Permissions
Restrict access based on user roles:
```python
from strawberry.permission import BasePermission

class IsAuthenticated(BasePermission):
    message = "User is not authenticated"

    def has_permission(self, source, info):
        return info.context.request.user.is_authenticated
```

### Subscriptions
Real-time updates using WebSockets:
```python
import asyncio
from strawberry.subscriptions import GRAPHQL_TRANSPORT_WS_PROTOCOL

@strawberry.subscription
async def count_to_ten() -> int:
    for i in range(1, 11):
        await asyncio.sleep(1)
        yield i
```

### Testing GraphQL APIs
Use Django's test client:
```python
from strawberry.django.test.client import GraphQLTestClient

client = GraphQLTestClient(schema)

response = client.query("""
query {
  books {
    title
  }
}
""")
assert response.data["books"] == ["Django for Beginners"]
```

---



## Schema Definition

### Types
```python
import strawberry
from typing import List, Optional

@strawberry.type
class Book:
    id: int
    title: str
    author: str
    published_year: Optional[int] = None
    genres: List[str] = strawberry.field(default_factory=list)

@strawberry.input
class BookInput:
    title: str
    author: str
    published_year: Optional[int] = None
    genres: List[str] = strawberry.field(default_factory=list)
```

### Queries
```python
@strawberry.type
class Query:
    @strawberry.field
    def books(self) -> List[Book]:
        return get_books()

    @strawberry.field
    def book(self, id: int) -> Optional[Book]:
        return get_book_by_id(id)
```

### Mutations
```python
@strawberry.type
class Mutation:
    @strawberry.mutation
    def create_book(self, book_data: BookInput) -> Book:
        return create_book(**book_data.__dict__)

    @strawberry.mutation
    def delete_book(self, id: int) -> bool:
        return delete_book(id)
```

### Schema Setup
```python
schema = strawberry.Schema(query=Query, mutation=Mutation)
```

## Advanced Features

### Enums
```python
@strawberry.enum
class BookStatus(str):
    AVAILABLE = "AVAILABLE"
    BORROWED = "BORROWED"
    LOST = "LOST"
```

### Interfaces
```python
@strawberry.interface
class Item:
    id: int
    title: str

@strawberry.type
class Book(Item):
    author: str

@strawberry.type
class Magazine(Item):
    publisher: str
```

### Field Arguments
```python
@strawberry.type
class Query:
    @strawberry.field
    def books(
        self,
        limit: Optional[int] = 10,
        offset: Optional[int] = 0,
        author: Optional[str] = None
    ) -> List[Book]:
        return get_books(limit=limit, offset=offset, author=author)
```

### Custom Scalars
```python
@strawberry.scalar
class DateTime:
    @staticmethod
    def serialize(value) -> str:
        return value.isoformat()

    @staticmethod
    def parse_value(value: str) -> datetime:
        return datetime.fromisoformat(value)
```

### Context
```python
@strawberry.type
class Query:
    @strawberry.field
    def current_user(self, info) -> Optional[User]:
        return info.context.user
```

---

# Django-Strawberry Guide

## Setup
```python
pip install strawberry-graphql-django
```

## settings.py
```python
INSTALLED_APPS = [
    ...
    'strawberry.django',
    ...
]

MIDDLEWARE = [
    ...
    'strawberry.django.middleware.GraphQLMiddleware',
]
```

## Types with Django Models

### Model Definition
```python
from django.db import models

class Book(models.Model):
    title = models.CharField(max_length=100)
    author = models.CharField(max_length=100)
    published_year = models.IntegerField(null=True)
    created_at = models.DateTimeField(auto_now_add=True)
```

### GraphQL Type
```python
import strawberry
from strawberry import auto
from strawberry.django import type
from typing import List

@type
class Book:
    id: auto
    title: auto
    author: auto
    published_year: auto
    created_at: auto

@strawberry.input
class BookInput:
    title: str
    author: str
    published_year: int | None = None
```

### Queries with Django Models
```python
from strawberry.django import auth
from strawberry.types import Info
from django.db.models import Q

@strawberry.type
class Query:
    @strawberry.field
    def books(
        self,
        info: Info,
        search: str | None = None
    ) -> List[Book]:
        qs = models.Book.objects.all()
        
        if search:
            qs = qs.filter(
                Q(title__icontains=search) |
                Q(author__icontains=search)
            )
        
        return qs

    @strawberry.field
    @auth.login_required
    def my_books(self, info: Info) -> List[Book]:
        return models.Book.objects.filter(user=info.context.request.user)
```

### Mutations with Django Models
```python
@strawberry.type
class Mutation:
    @strawberry.mutation
    @auth.login_required
    def create_book(self, info: Info, input: BookInput) -> Book:
        book = models.Book.objects.create(
            user=info.context.request.user,
            **input.__dict__
        )
        return book

    @strawberry.mutation
    @auth.login_required
    def update_book(
        self,
        info: Info,
        id: int,
        input: BookInput
    ) -> Book:
        book = models.Book.objects.get(
            id=id,
            user=info.context.request.user
        )
        for key, value in input.__dict__.items():
            setattr(book, key, value)
        book.save()
        return book
```

### Relationships
```python
class Author(models.Model):
    name = models.CharField(max_length=100)

class Book(models.Model):
    title = models.CharField(max_length=100)
    author = models.ForeignKey(Author, on_delete=models.CASCADE)
    genres = models.ManyToManyField('Genre')

@type
class Author:
    id: auto
    name: auto
    books: List['Book']

@type
class Book:
    id: auto
    title: auto
    author: Author
    genres: List['Genre']
```

### Permissions
```python
from strawberry.django import permissions
from strawberry.types import Info

class IsBookOwner(permissions.BasePermission):
    message = "You can't access this book"

    def has_permission(self, source: Any, info: Info, **kwargs) -> bool:
        return source.user == info.context.request.user

@strawberry.type
class Query:
    @strawberry.field
    @auth.login_required
    @permissions.permission_classes([IsBookOwner])
    def book(self, info: Info, id: int) -> Book:
        return models.Book.objects.get(id=id)
```

### Custom Context
```python
# context.py
from strawberry.django.context import StrawberryDjangoContext

class CustomContext(StrawberryDjangoContext):
    def get_current_user(self):
        return self.request.user if self.request else None

# urls.py
from strawberry.django.views import GraphQLView
from .context import CustomContext

urlpatterns = [
    path('graphql/', GraphQLView.as_view(
        schema=schema,
        context_class=CustomContext
    )),
]
```

### File Uploads
```python
@strawberry.type
class Mutation:
    @strawberry.mutation
    async def upload_book_cover(
        self,
        info: Info,
        file: Upload,
        book_id: int
    ) -> Book:
        content = await file.read()
        book = models.Book.objects.get(id=book_id)
        book.cover.save(file.filename, ContentFile(content))
        return book
```

### Testing
```python
from strawberry.django.test import GraphQLTestCase

class BookTestCase(GraphQLTestCase):
    def test_books_query(self):
        response = self.query(
            '''
            query {
                books {
                    id
                    title
                }
            }
            '''
        )
        self.assertEqual(response.status_code, 200)
        self.assertResponseNoErrors(response)
```

### Mini-Project: Library Management API
- Models: Book, Author
- Queries: Fetch books and authors
- Mutations: Add books
- Authentication: Restrict adding books to authenticated users

---

## 6. Gotchas
- **N+1 Query Problem**: Use dataloaders to avoid excessive database queries.
- **Schema Updates**: Always test after modifying schemas to prevent breaking changes.
- **Context Management**: Ensure the `info.context` object is properly set up.

---

## 7. Common Pitfalls
- **Over-fetching Data**: Ensure queries request only necessary fields.
- **Improper Error Handling**: Always handle resolver exceptions gracefully.
- **Missing Permissions**: Secure mutations and queries to prevent unauthorized access.

---

## 8. Best Practices
- **Modular Schema**: Split large schemas into smaller, manageable parts.
- **Versioning**: Implement API versioning for long-term maintainability.
- **Documentation**: Use introspection and tools like GraphiQL for API docs.
- **Testing**: Write unit tests for resolvers and integrations.

---

# MISC
- understand dataclasses properly in python.
- solving N+1 problem in strawberry

