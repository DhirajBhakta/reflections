# Django


### Tutorial
- venv + install django
- `django-admin startproject myproject`
- `cd myproject && python manage.py runserver`

### Apps
`python manage.py startapp posts`
`python manage.py startapp another_app`

### urls.py

What is "Path Converters"?
- str, int, slug, uuid, path

`from django.urls import reverse`


### Views
`from django.http import HttpResponse`

### Models
`python manage.py shell`
Shell is the best way to experiment with models

When you make model changes...
```
python manage.py makemigrations
python mange.py migrate
```

### Templates
...every "app" has its own templates dir.
`from django.shortcuts import render`

Use Double paranthesis to access vars passed to template eg: `<h1>Welcome - {{name}}</h1>`

Variables(builtin):::
Other variables ::: (forloop.first, forloop.last, forloop.counter, forloop.counter0)

Tags::
```
{% for post in posts %}
    <a href="{% url 'post' post.id %}"><h1>{{post.title}}</h1></a>
    <p>{{post.content}}</p>
{% endfor %}
```
Other tags::: (if-elif-endif , empty )

filters(for transformations):::
`{{variable|filter}}`
eg: `{{post.title|title}}`
Other filters::: (truncate)

Template Inheritance::: (layout.html)
`{% extends "layout.html" %}` at the top of other templates.

Blocks:::
```
{% block body %}
    <h1>{{post.title}</h1>
    <p>{{post.content}}</p>
{% endblock body %}
```

Include:::
`{% include "posts/includes/postcard.html" %}`

Context Processors:::
functions which return a dict which is accessible in templates.
You must register the context processors in settings.py
### Static
`{% load static %}` at the top of other templates
```
{% block css %}
    <link rel="stylesheet" href="{% static "posts/home.css" %}">
{% endblock css %}
```
### Static media
> **Note**: This will store all uploaded images(artifacts) in static/ folder.
May not be what you want in production!

In urls.py
```
from django.conf.urls.static import static
from django.conf import settings

urlpatterns = [
    ...
]
urlpatterns += static(settings.MEDIA_URL)
```

### Forms
```html
<form action="{% url 'users:logout' %}" method="post">
    {% csrf_token %}
</form>
```

```
from django import forms
from . import models

class CreatePost(forms.ModelForm):
    class Meta:
        model = models.Post
        fields = ['title', 'body']
```

you can then use this form object , passing it to `render` in views.py
```
@login_required(login_url="/users/login/")
def post_new(request):
    form = forms.CreatePost()
    return render(request, 'posts/post_new.html', {'form': form})
```

### Django Admin
`python manage.py createsuperuser`

Register your models in `admin.py`
`admin.site.register(Post)`


### Built in User Management
`from django.contrib.auth.forms import UserCreationForm, AuthenticationForm`
You can use this form object while passing to `render` into a template.
`from django.contrib.auth import login,logout`
`from django.contrib.auth.decorators import login_required`
```
if form.is_valid():
    login(request, form.get_user())
```


### Settings.py
```
STATIC_URL= '/static'
STATICFILES_DIRS = [
    os.path.join(BASE_DIR,'static')
]
MEDIA_URL = 'media/'
MEDIA_ROOT = os.path.join(BASE_DIR, 'media')
```



# Misc
- what is __pycache__ ?
- what is apps.py inside each app?
- what exactly is a queryset? `Post.objects.all()`
- what is `app_name` in urls.py ?
- what is CSRF attack and CSRFtoken ? how to use `{% csrf_token %}` in django forms?

