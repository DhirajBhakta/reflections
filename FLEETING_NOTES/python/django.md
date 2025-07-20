# Django 

### Initial Setup
1. Create and activate virtual environment (venv)
2. Install Django: `pip install django`
3. Create new project: `django-admin startproject myproject`
4. Start development server: `cd myproject && python manage.py runserver`

### Creating Apps
Django projects are divided into apps (reusable components):
```python
python manage.py startapp posts
python manage.py startapp another_app
```
Remember to add new apps to `INSTALLED_APPS` in settings.py

## URL Configuration

### URL Patterns
URLs are configured in `urls.py` using the `path()` function.

### Path Converters
Convert URL parameters to Python types:
- `str`: Matches any non-empty string (excluding '/')
- `int`: Matches positive integers
- `slug`: Matches slug strings (letters, numbers, hyphens, underscores)
- `uuid`: Matches UUID strings
- `path`: Matches complete URL paths including '/'

### URL Reversing
Use `reverse()` to dynamically generate URLs:
```python
from django.urls import reverse
url = reverse('post-detail', args=[post.id])
```

## Views

### Basic Views
```python
from django.http import HttpResponse
from django.shortcuts import render

def home(request):
    return HttpResponse("Hello, World!")
```

## Models and Database

### Working with Models
- Use Django shell for experimenting: `python manage.py shell`
- QuerySets: Database-abstraction API (e.g., `Post.objects.all()`)
  - Lazy evaluation: QuerySets are only executed when needed
  - Chainable operations: filter(), exclude(), order_by()

### Database Migrations
After model changes:
```python
python manage.py makemigrations  # Create migration files
python manage.py migrate         # Apply migrations to database
```

## Templates

### Template Structure
Each app can have its own templates directory:
```
app_name/
    templates/
        app_name/
            template.html
```

### Template Variables
- Access context variables: `{{ variable_name }}`
- Built-in template variables:
  - `forloop.first`: True on first iteration
  - `forloop.last`: True on last iteration
  - `forloop.counter`: 1-based counter
  - `forloop.counter0`: 0-based counter
  - ... there are many more...

### Template Tags
```django
{% for item in items %}
    {{ item }}
{% empty %}
    No items found.
{% endfor %}

{% if condition %}
    Content
{% elif other_condition %}
    Other content
{% endif %}
```

### Filters
Transform variable output:
```django
{{ variable|filter_name }}
{{ post.title|title }}         # Capitalize words
{{ text|truncatewords:30 }}    # Truncate to 30 words
```

### Template Inheritance
Base template (layout.html):
```django
{% block content %}
{% endblock content %}
```

Child templates:
```django
{% extends "layout.html" %}

{% block content %}
    <h1>{{ page_title }}</h1>
{% endblock content %}
```

### Including Templates
```django
{% include "path/to/template.html" %}
```

### Context Processors
Functions that add variables to template context globally:
1. Create processor function returning a dictionary
2. Add to `TEMPLATES` setting in settings.py:
```python
TEMPLATES = [{
    'OPTIONS': {
        'context_processors': [
            'myapp.context_processors.my_processor',
        ],
    },
}]
```

### Elaborate Template examples
Template inheritance is one of Django's most powerful features. It lets you build a base "skeleton" template containing common elements and define blocks that child templates can override.

#### Base Template (layout.html)
```html
<!DOCTYPE html>
<html>
<head>
    <title>{% block title %}My Site{% endblock title %}</title>
    {% block css %}
        <link rel="stylesheet" href="{% static 'css/base.css' %}">
    {% endblock css %}
</head>
<body>
    <header>
        <nav>
            {% block nav %}
                <ul>
                    <li><a href="{% url 'home' %}">Home</a></li>
                    <li><a href="{% url 'about' %}">About</a></li>
                    {% if user.is_authenticated %}
                        <li>
                            <form action="{% url 'users:logout' %}" method="post">
                                {% csrf_token %}
                                <button type="submit">Logout</button>
                            </form>
                        </li>
                    {% else %}
                        <li><a href="{% url 'users:login' %}">Login</a></li>
                    {% endif %}
                </ul>
            {% endblock nav %}
        </nav>
    </header>

    <main>
        {% block messages %}
            {% if messages %}
                <div class="messages">
                    {% for message in messages %}
                        <div class="message {{ message.tags }}">
                            {{ message }}
                        </div>
                    {% endfor %}
                </div>
            {% endif %}
        {% endblock messages %}

        {% block content %}
        {% endblock content %}
    </main>

    <footer>
        {% block footer %}
            <p>&copy; {% now "Y" %} My Site. All rights reserved.</p>
        {% endblock footer %}
    </footer>

    {% block js %}
        <script src="{% static 'js/base.js' %}"></script>
    {% endblock js %}
</body>
</html>
```

#### Child Template Example (post_detail.html)
```html
{% extends "layout.html" %}

{% block title %}{{ post.title }} - My Site{% endblock title %}

{% block css %}
    {{ block.super }}  {# Include parent block's content #}
    <link rel="stylesheet" href="{% static 'css/post.css' %}">
{% endblock css %}

{% block content %}
    <article>
        <h1>{{ post.title }}</h1>
        <div class="post-meta">
            Posted by {{ post.author }} on {{ post.created_at|date:"F j, Y" }}
        </div>
        {{ post.content|safe }}

        {% if user == post.author %}
            <div class="post-actions">
                <a href="{% url 'posts:edit' post.pk %}" class="btn">Edit</a>
                <form action="{% url 'posts:delete' post.pk %}" method="post" class="inline-form">
                    {% csrf_token %}
                    <button type="submit" class="btn btn-danger" onclick="return confirm('Are you sure?')">
                        Delete
                    </button>
                </form>
            </div>
        {% endif %}
    </article>

    <section class="comments">
        <h2>Comments</h2>
        <form action="{% url 'posts:add_comment' post.pk %}" method="post">
            {% csrf_token %}
            {{ comment_form.as_p }}
            <button type="submit">Add Comment</button>
        </form>
    </section>
{% endblock content %}
```

Key Points:
1. Use `{% extends %}` at the very top of child templates
2. Each `{% block %}` in the parent can be overridden by children
3. Use `{{ block.super }}` to include parent block's content
4. Blocks can be nested
5. Block names should be descriptive and consistent
6. Common blocks: title, content, css, js, nav, footer
7. Forms within templates often use URL tags for their action attributes
8. Always include `{% csrf_token %}` in POST forms
9. You can have default content in parent template blocks
10. Child templates only need to override the blocks they want to change

## Static Files

### Configuration
```python
# settings.py
STATIC_URL = '/static/'
STATICFILES_DIRS = [
    os.path.join(BASE_DIR, 'static')
]
MEDIA_URL = 'media/'
MEDIA_ROOT = os.path.join(BASE_DIR, 'media')
```

### Usage
```django
{% load static %}
<link href="{% static 'css/style.css' %}" rel="stylesheet">
```

### Media Files
Configure URLs for uploaded files:
```python
# urls.py
from django.conf import settings
from django.conf.urls.static import static

urlpatterns = [
    # ... your URL patterns ...
] + static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
```

## Forms

### Form Creation
```python
from django import forms
from . import models

class PostForm(forms.ModelForm):
    class Meta:
        model = models.Post
        fields = ['title', 'body']
```

### Form Usage
```python
@login_required(login_url="/users/login/")
def post_new(request):
    if request.method == "POST":
        form = PostForm(request.POST)
        if form.is_valid():
            post = form.save()
            return redirect('post_detail', pk=post.pk)
    else:
        form = PostForm()
    return render(request, 'posts/post_new.html', {'form': form})
```

### Template Usage
```django
<form method="post">
    {% csrf_token %}
    {{ form.as_p }}
    <button type="submit">Save</button>
</form>
```

## Authentication

### User Management
```python
from django.contrib.auth.forms import UserCreationForm, AuthenticationForm
from django.contrib.auth import login, logout
from django.contrib.auth.decorators import login_required

def login_view(request):
    if request.method == 'POST':
        form = AuthenticationForm(data=request.POST)
        if form.is_valid():
            login(request, form.get_user())
            return redirect('home')
    else:
        form = AuthenticationForm()
    return render(request, 'accounts/login.html', {'form': form})
```

## Admin Interface

### Setup
1. Create superuser: `python manage.py createsuperuser`
2. Register models in admin.py:
```python
from django.contrib import admin
from .models import Post

admin.site.register(Post)
```

## Common Questions

### What is __pycache__?
Directory containing compiled Python files (.pyc) for faster loading.

### What is apps.py?
Contains app configuration class for customizing app attributes and initialization.

### What is a QuerySet?
Database-abstraction API that lets you retrieve, filter, and manipulate data without writing SQL.

### What is app_name in urls.py?
Namespace for URL patterns to avoid naming conflicts between apps.

### What is CSRF?
Cross-Site Request Forgery protection:
- Prevents unauthorized commands from authenticated users
- `{% csrf_token %}` adds a hidden form field with a token
- Django validates token on form submission
