package net.qiujuer.sample.blur;

import android.graphics.Bitmap;
import android.os.Build;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.ViewTreeObserver;
import android.support.v4.app.FragmentManager;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.Switch;
import android.widget.CompoundButton;
import net.qiujuer.sample.blur.frags.BaseFragment;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {
    BaseFragment mJniBitmap;
    BaseFragment mJava;
    private SeekBar sb_radius;
    TextView tv_radius;
    int radius = 0;
    Boolean flag_java = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        sb_radius = (SeekBar) findViewById(R.id.seekBar);
        tv_radius = (TextView) findViewById(R.id.textView);
        sb_radius.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int i, boolean fromUser) {
                switch (seekBar.getId()) {
                    case R.id.seekBar:
                        tv_radius.setText(String.valueOf(i));
                        radius = i;
                        break;

                }
                start(radius);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });


        findFragments();

        findViewById(R.id.btn_opt).setOnClickListener(this);
    }

    private void findFragments() {
        FragmentManager manager = getSupportFragmentManager();
        mJniBitmap = (BaseFragment) manager.findFragmentById(R.id.frag_jni_bitmap);
        mJava = (BaseFragment) manager.findFragmentById(R.id.frag_java);
    }


    private void start(final int radius) {
        final View root = findViewById(R.id.root);
        root.getViewTreeObserver().addOnPreDrawListener(new ViewTreeObserver.OnPreDrawListener() {
            @Override
            public boolean onPreDraw() {
                root.getViewTreeObserver().removeOnPreDrawListener(this);
                root.buildDrawingCache();
                Bitmap bmp = root.getDrawingCache();
                setFragmentsBitmap(bmp, radius);
                return true;
            }
        });
    }

    private void setFragmentsBitmap(final Bitmap bmp, final int radius) {
        Thread thread = new Thread() {
            @Override
            public void run() {
                super.run();
                    mJniBitmap.setBitmap(bmp, radius);
                    mJava.setBitmap(bmp, radius);
            }
        };
        thread.start();
    }

    @Override
    public void onClick(View v) {
        start(0);
        v.setVisibility(View.GONE);
    }
}
