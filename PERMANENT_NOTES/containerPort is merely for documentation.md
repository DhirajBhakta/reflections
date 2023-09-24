```yaml
apiVersion: v1
kind: Pod
metadata:
  name: nginx
spec:
  containers:
  - name: python
    image: python:alpine
    command: ["python", "-m", "http.server", "8080"]
    ports:
    - containerPort: 80
```

the `containerPort` in `ports` does NOTHING. You can run your application in whatever port you want and even specify a totally different port in `containerPort` and it should still work!

`containerPort` exists SOLELY for **documentation purpose**