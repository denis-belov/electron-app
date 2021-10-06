import './index.scss';
import '@babel/polyfill';



const
	{
		testRenderingThread,
		runRenderingThread,
		testPixelData,
		getPixelData,
		_tran,
	}	= window.__CPP_MODULE__;



const canvas = document.createElement('canvas');
canvas.width = 800;
canvas.height = 600;
canvas.style.position = 'absolute';
canvas.style.width = '800px';
canvas.style.height = '600px';



const rotateOrbit = (evt) =>
{
	_tran(-evt.movementX * 0.01, -evt.movementY * 0.01);
};

const stopOrbitRotation = () =>
{
	canvas.removeEventListener('mousemove', rotateOrbit);
	window.removeEventListener('mouseup', stopOrbitRotation);
};

canvas.addEventListener
(
	'mousedown',

	() =>
	{
		canvas.addEventListener('mousemove', rotateOrbit);
		window.addEventListener('mouseup', stopOrbitRotation);
	},
);

window.addEventListener('mouseup', stopOrbitRotation);



const canvas_context = canvas.getContext('2d');

document.body.appendChild(canvas);

const image_data = canvas_context.createImageData(800, 600);



window.addEventListener
(
	'load',

	async () =>
	{
		if (!testRenderingThread())
		{
			runRenderingThread();
		}

		let interval = null;

		await new Promise
		(
			(resolve) =>
			{
				interval =
					setInterval
					(
						() =>
						{
							if (testPixelData())
							{
								clearInterval(interval);

								resolve();
							}
						},

						1000,
					);
			},
		);

		// const image_data = new ImageData(getPixelData(), 800, 600);
		// image_data.data = getPixelData();

		const render = () =>
		{
			image_data.data.set(getPixelData());

			canvas_context.putImageData(image_data, 0, 0);

			requestAnimationFrame(render);
		};

		render();
	},
);
