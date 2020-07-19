build: Dockerfile
	docker build -t ncd .

run:
	cd .. && docker run --mount type=bind,src=$(PWD)/../expdir,dst=/expdir -it ncd bash
